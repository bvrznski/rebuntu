// rebuntu::runtime::cancellation::token — Cancellation Token (Phase 4.0)
//
// CancellationToken provides a thread-safe mechanism for propagating
// cancellation requests through the execution stack.
//
// Key properties:
// - Thread-safe: can be used from multiple threads
// - Non-owning: references shared state, no ownership cycle risk
// - Callback-based: allows components to register handlers
// - Atomic: uses std::atomic for zero-lock operation in steady state

#pragma once

#include <runtime/cancellation/error.hpp>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <mutex>
#include <optional>

namespace rebuntu::runtime {

// Forward declaration
class CancellationToken;

// State struct must be defined before(CancellationToken) uses it
struct CancellationTokenState {
    std::atomic<bool> cancelled{false};
    mutable std::mutex mutex;
    std::optional<std::string> reason;
    int next_callback_id_ = 0;
    std::unordered_map<int, std::function<void()>> callbacks_;
};

class CancellationToken {
public:
    // Create a new token (not cancelled)
    CancellationToken() 
        : state_(std::make_shared<CancellationTokenState>()) {}
    
    // Check if cancellation has been requested
    bool is_cancelled() const {
        return state_->cancelled.load(std::memory_order_acquire);
    }
    
    // Get the current reason for cancellation (if any)
    std::optional<std::string> cancellation_reason() const {
        if (!is_cancelled()) {
            return std::nullopt;
        }
        std::lock_guard lock(state_->mutex);
        return state_->reason;
    }
    
    // Request cancellation with optional reason
    void request_cancel(std::optional<std::string> reason = std::nullopt) {
        // Fast path: already cancelled
        if (is_cancelled()) {
            return;
        }
        
        // Slow path: acquire lock and set state
        std::vector<std::function<void()>> callbacks_to_invoke;
        {
            std::lock_guard lock(state_->mutex);
            if (!state_->cancelled.exchange(true, std::memory_order_release)) {
                // Just transitioned to cancelled
                state_->reason = std::move(reason);
                // Copy callbacks before releasing the lock
                for (const auto& [id, cb] : state_->callbacks_) {
                    callbacks_to_invoke.push_back(cb);
                }
            }
        }  // Release lock before calling callbacks
        
        // Invoke all registered callbacks (no lock held)
        for (auto& cb : callbacks_to_invoke) {
            cb();
        }
    }
    
    // Register a callback to be invoked when cancellation is requested
    // Returns an ID that can be used to unregister
    int register_callback(std::function<void()> callback) {
        if (!callback) {
            return -1;  // Invalid callback
        }
        
        std::lock_guard lock(state_->mutex);
        
        // Fast path: already cancelled, invoke immediately
        bool was_cancelled = state_->cancelled.load(std::memory_order_acquire);
        if (was_cancelled) {
            callback();
            return 0;
        }
        
        int id = ++state_->next_callback_id_;
        state_->callbacks_[id] = std::move(callback);
        return id;
    }
    
    // Unregister a previously registered callback
    void unregister_callback(int callback_id) {
        if (callback_id <= 0) {
            return;  // Invalid ID
        }
        
        std::lock_guard lock(state_->mutex);
        state_->callbacks_.erase(callback_id);
    }
    
    // Create a child token that inherits parent's state
    CancellationToken make_child_token() const {
        CancellationToken child;
        child.state_ = state_;
        return child;
    }
    
    // Check if this token is valid (has backing state)
    bool is_valid() const {
        return static_cast<bool>(state_);
    }

private:
    std::shared_ptr<CancellationTokenState> state_;
};

}  // namespace rebuntu::runtime
