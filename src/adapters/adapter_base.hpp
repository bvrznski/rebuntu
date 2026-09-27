// rebuntu::adapters::AdapterBase — Bounded Timeout/Cancellation Support Base (Phase 5.49)
//
// This module provides common timeout and cancellation infrastructure for all
// discovery adapters. It enables bounded execution with configurable deadlines.
//
// Design Principles:
//   - All adapters inherit from AdapterBase to get timeout/cancellation support
//   - Timeouts are enforced at the adapter level, not at individual operations
//   - Cancellation is cooperative via flag checking
//   - Timeout != cancellation: timeout is a deadline, cancellation is external

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <chrono>
#include <optional>
#include <atomic>
#include <thread>
#include <mutex>

namespace rebuntu::adapters {

// ============================================================================
// CancellationState — Cooperative cancellation state
//
// Manages cooperative cancellation for adapter operations:
//   - cancel(): Request cancellation (thread-safe)
//   - is_cancelled(): Check if cancellation was requested
//
// Note: This is NOT a hard termination mechanism. Implementations must
// periodically check is_cancelled() and abort gracefully.
// ============================================================================
class CancellationState {
public:
    CancellationState() = default;

    // Request cancellation (thread-safe, idempotent)
    void request_stop() noexcept {
        cancelled_.store(true);
    }

    // Check if cancellation was requested
    bool is_cancelled() const noexcept {
        return cancelled_.load();
    }

    // Reset cancellation state (for reuse)
    void reset() noexcept {
        cancelled_.store(false);
    }

private:
    std::atomic<bool> cancelled_{false};
};

// ============================================================================
// AdapterBase — Base class for all adapters with timeout/cancellation
//
// Provides common infrastructure:
//   - Timeout configuration via duration
//   - Cooperative cancellation via CancellationState
//   - Deadline tracking for bounded execution
//
// All discovery adapters should inherit from this to get consistent
// timeout and cancellation behavior.
// ============================================================================
class AdapterBase {
public:
    // Constructor with default timeout (10 seconds)
    explicit AdapterBase(std::chrono::milliseconds default_timeout = std::chrono::seconds(10))
        : current_timeout_(default_timeout) {}

    virtual ~AdapterBase() = default;

    // ============================================================================
    // Timeout Configuration
    // ============================================================================

    // Set the timeout for subsequent operations
    void set_timeout(std::chrono::milliseconds timeout) {
        std::lock_guard<std::mutex> lock(mutex_);
        current_timeout_ = timeout;
    }

    // Get current effective timeout
    std::chrono::milliseconds get_timeout() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return current_timeout_;
    }

    // ============================================================================
    // Cancellation
    // ============================================================================

    // Request cancellation of pending operations
    void cancel() noexcept {
        cancellation_state_.request_stop();
    }

    // Check if cancellation was requested
    bool is_cancelled() const noexcept {
        return cancellation_state_.is_cancelled();
    }

    // Reset the cancellation state (for reuse)
    void reset_cancellation() noexcept {
        cancellation_state_.reset();
    }

    // ============================================================================
    // Deadline Tracking (internal helpers)
    // ============================================================================

    // Record operation start time for relative timeout tracking
    void record_operation_start() {
        std::lock_guard<std::mutex> lock(mutex_);
        last_operation_start_ = std::chrono::system_clock::now();
    }

    // Check if we're past the deadline (considering current timeout)
    bool is_past_deadline() const {
        std::lock_guard<std::mutex> lock(mutex_);
        
        auto now = std::chrono::system_clock::now();
        
        // If last_operation_start_ hasn't been set, no deadline check possible
        if (!last_operation_start_.time_since_epoch().count()) {
            return false;
        }
        
        auto effective_timeout = current_timeout_;
        if (effective_timeout.count() > 0) {
            auto deadline = last_operation_start_ + effective_timeout;
            return now >= deadline;
        }
        
        return false;
    }

protected:
    mutable std::mutex mutex_;
    
    // Timeout configuration
    std::chrono::milliseconds current_timeout_;

    // Operation tracking
    std::chrono::system_clock::time_point last_operation_start_{};

    // Cancellation state
    mutable CancellationState cancellation_state_;
};

// ============================================================================
// TimeoutResult — Result wrapper that includes timeout information
//
// Extends core outcomes with timing and cancellation metadata.
// ============================================================================
template<typename T>
struct TimeoutResult {
    using value_type = T;

    core::SemanticStatus status;
    std::string description;

    // The actual result value (if successful)
    std::optional<T> value;

    // Timing information
    std::chrono::milliseconds elapsed_ms{0};
    bool is_timeout{false};        // True if operation timed out
    bool is_cancelled{false};      // True if operation was cancelled

    // Error details (for non-success status)
    core::Error err;

    // Factory methods for common outcomes
    static TimeoutResult success(T&& val, std::chrono::milliseconds elapsed) {
        TimeoutResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = std::move(val);
        r.elapsed_ms = elapsed;
        return r;
    }

    static TimeoutResult timeout(std::string desc, std::chrono::milliseconds elapsed) {
        TimeoutResult r;
        r.status = core::SemanticStatus::kFailure;
        r.description = std::move(desc);
        r.elapsed_ms = elapsed;
        r.is_timeout = true;
        return r;
    }

    static TimeoutResult cancelled(std::string desc, std::chrono::milliseconds elapsed) {
        TimeoutResult r;
        r.status = core::SemanticStatus::kFailure;
        r.description = std::move(desc);
        r.elapsed_ms = elapsed;
        r.is_cancelled = true;
        return r;
    }

    static TimeoutResult error(std::string code, std::string msg, std::chrono::milliseconds elapsed) {
        TimeoutResult r;
        r.status = core::SemanticStatus::kFailure;
        r.err.code = std::move(code);
        r.err.message = std::move(msg);
        r.elapsed_ms = elapsed;
        return r;
    }
};

// ============================================================================
// BoundedAdapter — Template base for adapters with typed results
//
// Extends AdapterBase with type-specific bounded operations.
// ============================================================================
template<typename ResultType>
class BoundedAdapter : public AdapterBase {
public:
    using Base = AdapterBase;
    
    explicit BoundedAdapter(std::chrono::milliseconds default_timeout = std::chrono::seconds(10))
        : AdapterBase(default_timeout) {}

    // Execute an operation with this adapter's configured timeout
    template<typename Func>
    auto execute_with_timeout(Func&& func)
        -> TimeoutResult<typename ResultType::value_type> {
        
        using ResultValueType = typename ResultType::value_type;
        
        record_operation_start();
        auto start_time = std::chrono::steady_clock::now();

        // Check for cancellation before starting
        if (is_cancelled()) {
            return TimeoutResult<ResultValueType>::cancelled(
                "Operation cancelled before execution",
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start_time));
        }

        auto timeout = get_timeout();
        
        // Check deadline before starting
        if (is_past_deadline()) {
            return TimeoutResult<ResultValueType>::timeout(
                "Operation past deadline",
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start_time));
        }

        try {
            auto result = func();
            
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start_time);
            
            return TimeoutResult<ResultValueType>::success(
                std::move(result), elapsed);
            
        } catch (const std::system_error& e) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start_time);
            
            if (e.code() == std::errc::operation_canceled ||
                e.code() == std::errc::interrupted) {
                return TimeoutResult<ResultValueType>::cancelled(
                    "Operation was interrupted",
                    elapsed);
            }
            
            return TimeoutResult<ResultValueType>::error(
                "E_SYSTEM_ERROR", e.what(),
                elapsed);
                
        } catch (const std::exception& e) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start_time);
            
            return TimeoutResult<ResultValueType>::error(
                "E_EXCEPTION", e.what(),
                elapsed);
                
        } catch (...) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start_time);
            
            return TimeoutResult<ResultValueType>::error(
                "E_UNKNOWN", "Unknown error",
                elapsed);
        }
    }

protected:
    using Base::is_cancelled;
    using Base::get_timeout;
    using Base::record_operation_start;
    using Base::is_past_deadline;
};

}  // namespace rebuntu::adapters