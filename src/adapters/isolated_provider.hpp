// rebuntu::adapters::isolated_provider — Provider Isolation and Degradation (Task 5.50)
//
// This module provides isolation mechanisms for discovery adapters to ensure
// that a failed optional provider produces DEGRADED/UNAVAILABLE observations
// without crashing unrelated discovery.
//
// Key Principles:
//   - Observation != inference: Only record what was actually observed
//   - Missing evidence != absence: UNKNOWN is not PASS or FAILURE
//   - Isolated failure: One adapter's crash doesn't affect others
//   - Evidence preservation: Store failure details for diagnosis

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <optional>
#include <type_traits>
#include <functional>
#include <utility>

namespace rebuntu::adapters {

// ============================================================================
// ProviderFailure — Record of an adapter failure with evidence
//
// Captures the failure mode, timing, and any available diagnostic information.
// This is NOT a stack trace (which could leak secrets), but observable facts
// about what went wrong during observation.
// ============================================================================

struct ProviderFailure {
    std::string provider_id;              // Which provider failed
    
    // When the failure occurred
    std::chrono::system_clock::time_point failure_time{};
    
    // Failure category (for filtering/analysis)
    enum class Category {
        kConnection,       // Could not connect to source
        kAuthentication,   // Authentication/authorization failed
        kPermission,       // Insufficient permissions
        kTimeout,          // Operation timed out
        kParseError,       // Failed to parse response
        kResourceExhausted,// Out of memory/descriptors
        kProtocolError,    // Unexpected protocol state
        kSystemError,      // OS-level error (fork, pipe, etc.)
        kUnknown,          // Unknown cause
    } category{Category::kUnknown};
    
    std::string category_string() const {
        switch (category) {
            case Category::kConnection:       return "connection";
            case Category::kAuthentication:   return "authentication";
            case Category::kPermission:       return "permission";
            case Category::kTimeout:          return "timeout";
            case Category::kParseError:       return "parse_error";
            case Category::kResourceExhausted:return "resource_exhausted";
            case Category::kProtocolError:    return "protocol_error";
            case Category::kSystemError:      return "system_error";
            case Category::kUnknown:          return "unknown";
        }
        return "unknown";
    }
    
    // Human-readable description (NO secret material)
    std::string description;
};

inline std::string to_string(const ProviderFailure& f) {
    return "ProviderFailure{" + f.provider_id + ", category=" + f.category_string() +
           ", time=" + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
               f.failure_time.time_since_epoch()).count()) +
           ", desc=" + f.description + "}";
}

// ============================================================================
// DegradedObservation<T> — Observation with optional failure evidence
//
// Wraps an observation result and includes any failures that occurred during
// the observation process. This allows callers to see both what was observed
// AND whether there were issues.
// ============================================================================

template<typename T>
struct DegradedObservation {
    // The primary observation (if successful)
    std::optional<T> value;
    
    // Status of this observation
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // Any failures that occurred during this specific observation
    std::vector<ProviderFailure> failures;
    
    // When this observation was made (for freshness tracking)
    std::chrono::system_clock::time_point observed_at{};
    
    // Factory methods for common outcomes
    
    static DegradedObservation success(T v, std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.value = std::move(v);
        o.status = core::SemanticStatus::kSuccess;
        o.observed_at = time;
        return o;
    }
    
    static DegradedObservation degraded(T v, std::vector<ProviderFailure> failures,
                                         std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.value = std::move(v);
        o.status = core::SemanticStatus::kCompleted;  // Work done but with issues
        o.failures = std::move(failures);
        o.observed_at = time;
        return o;
    }
    
    static DegradedObservation unavailable(std::vector<ProviderFailure> failures,
                                            std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.status = core::SemanticStatus::kUnknown;  // Outcome unknown
        o.failures = std::move(failures);
        o.observed_at = time;
        return o;
    }
    
    static DegradedObservation cancelled(std::string desc,
                                          std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.status = core::SemanticStatus::kCancelled;
        o.failures.push_back(ProviderFailure{
            .provider_id = "unknown",
            .failure_time = time,
            .category = ProviderFailure::Category::kUnknown,
            .description = std::move(desc),
        });
        o.observed_at = time;
        return o;
    }
    
    bool has_value() const { return value.has_value(); }
};

// ============================================================================
// DegradedObservation<void> specialization — void result handling
// ============================================================================

template<>
struct DegradedObservation<void> {
    // Status of this observation
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // Any failures that occurred during this specific observation
    std::vector<ProviderFailure> failures;
    
    // When this observation was made (for freshness tracking)
    std::chrono::system_clock::time_point observed_at{};
    
    // Factory methods for common outcomes
    
    static DegradedObservation success(std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.status = core::SemanticStatus::kSuccess;
        o.observed_at = time;
        return o;
    }
    
    static DegradedObservation degraded(std::vector<ProviderFailure> failures,
                                         std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.status = core::SemanticStatus::kCompleted;  // Work done but with issues
        o.failures = std::move(failures);
        o.observed_at = time;
        return o;
    }
    
    static DegradedObservation unavailable(std::vector<ProviderFailure> failures,
                                            std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.status = core::SemanticStatus::kUnknown;  // Outcome unknown
        o.failures = std::move(failures);
        o.observed_at = time;
        return o;
    }
    
    static DegradedObservation cancelled(std::string desc,
                                          std::chrono::system_clock::time_point time = {}) {
        DegradedObservation o;
        o.status = core::SemanticStatus::kCancelled;
        o.failures.push_back(ProviderFailure{
            .provider_id = "unknown",
            .failure_time = time,
            .category = ProviderFailure::Category::kUnknown,
            .description = std::move(desc),
        });
        o.observed_at = time;
        return o;
    }
    
    bool has_value() const { return false; }  // void has no value
};

// ============================================================================
// IsolatedProvider<T> — Wrapper that catches adapter failures
//
// This template wraps any adapter class T and provides exception-safe access.
// When an adapter method throws, the wrapper:
//   1. Catches the exception
//   2. Records it as a ProviderFailure with category
//   3. Returns DegradedObservation with kUnknown/kCompleted status
//   4. Does NOT crash the caller
//
// Design Notes:
//   - Isolation happens at the wrapper level, not inheritance
//   - The wrapped adapter's interface is preserved through delegation
//   - All public methods that can fail are wrapped in try-catch blocks
// ============================================================================

template<typename AdapterT>
class IsolatedProvider {
public:
    using WrappedType = AdapterT;
    
    explicit IsolatedProvider(std::unique_ptr<AdapterT> wrapped)
        : wrapped_(std::move(wrapped)), provider_id_("isolated-" + default_provider_id()) {}
    
    // Constructor with explicit provider ID
    IsolatedProvider(std::unique_ptr<AdapterT> wrapped, std::string provider_id)
        : wrapped_(std::move(wrapped)), provider_id_(std::move(provider_id)) {}
    
    ~IsolatedProvider() = default;
    
    // Get the original adapter (for direct access when isolation not needed)
    AdapterT* get_original() { return wrapped_.get(); }
    const AdapterT* get_original() const { return wrapped_.get(); }
    
    // Provider identification for logging/metrics
    const std::string& provider_id() const { return provider_id_; }
    
    // ========================================================================
    // Exception-safe wrapper for observe_all method
    //
    // Assumes the adapter has: auto observe_all() -> ResultType;
    // ========================================================================
    
    DegradedObservation<decltype(std::declval<AdapterT>().observe_all())> observe_all() {
        return execute_with_catch(&AdapterT::observe_all, "observe_all");
    }
    
    // ========================================================================
    // Get the wrapped adapter
    // ========================================================================
    
    AdapterT& operator*() { return *wrapped_; }
    const AdapterT& operator*() const { return *wrapped_; }
    
    AdapterT* operator->() { return wrapped_.get(); }
    const AdapterT* operator->() const { return wrapped_.get(); }

private:
    // Get a default provider ID from the wrapped adapter
    std::string default_provider_id() const {
        if (wrapped_) {
            if constexpr (requires { wrapped_->provider_id(); }) {
                return wrapped_->provider_id();
            }
        }
        return "unknown-adapter";
    }
    
    // Execute a member function pointer with exception handling - non-void case
    template<typename Func>
    auto execute_with_catch(Func&& func, const char* operation) -> 
        DegradedObservation<decltype(std::declval<AdapterT>().observe_all())> {
        
        using ResultType = decltype(std::declval<AdapterT>().observe_all());
        
        if (!wrapped_) {
            return DegradedObservation<ResultType>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kConnection,
                    .description = "Wrapped adapter is null",
                }
            });
        }
        
        try {
            auto result = (wrapped_.get()->*func)();
            return DegradedObservation<ResultType>::success(std::move(result));
        } catch (const std::system_error& e) {
            return handle_system_error(e, operation);
        } catch (const std::runtime_error& e) {
            return DegradedObservation<ResultType>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kSystemError,
                    .description = "Runtime error in " + std::string(operation) + ": " + e.what(),
                }
            });
        } catch (const std::exception& e) {
            return DegradedObservation<ResultType>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kUnknown,
                    .description = "Exception in " + std::string(operation) + ": " + e.what(),
                }
            });
        } catch (...) {
            return DegradedObservation<ResultType>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kUnknown,
                    .description = "Unknown exception in " + std::string(operation),
                }
            });
        }
    }
    
    // Execute a boolean-returning member function
    template<typename Func>
    auto execute_bool_with_catch(Func&& func, const char* operation) -> DegradedObservation<bool> {
        if (!wrapped_) {
            return DegradedObservation<bool>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kConnection,
                    .description = "Wrapped adapter is null",
                }
            });
        }
        
        try {
            bool result = (wrapped_.get()->*func)();
            return DegradedObservation<bool>::success(result);
        } catch (const std::system_error& e) {
            auto obs = handle_system_error(e, operation);
            obs.status = core::SemanticStatus::kUnknown;
            return obs;
        } catch (const std::exception& e) {
            return DegradedObservation<bool>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kUnknown,
                    .description = "Exception in " + std::string(operation) + ": " + e.what(),
                }
            });
        } catch (...) {
            return DegradedObservation<bool>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kUnknown,
                    .description = "Unknown exception in " + std::string(operation),
                }
            });
        }
    }
    
    // Execute a void-returning member function
    DegradedObservation<void> execute_void_with_catch(
        void (AdapterT::*func)(),
        const char* operation) {
        
        if (!wrapped_) {
            return DegradedObservation<void>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kConnection,
                    .description = "Wrapped adapter is null",
                }
            });
        }
        
        try {
            (wrapped_.get()->*func)();
            return DegradedObservation<void>::success();
        } catch (const std::system_error& e) {
            auto obs = handle_system_error(e, operation);
            obs.status = core::SemanticStatus::kUnknown;
            return obs;
        } catch (const std::exception& e) {
            return DegradedObservation<void>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kUnknown,
                    .description = "Exception in " + std::string(operation) + ": " + e.what(),
                }
            });
        } catch (...) {
            return DegradedObservation<void>::unavailable({
                ProviderFailure{
                    .provider_id = provider_id_,
                    .failure_time = std::chrono::system_clock::now(),
                    .category = ProviderFailure::Category::kUnknown,
                    .description = "Unknown exception in " + std::string(operation),
                }
            });
        }
    }
    
    // Convert system_error to DegradedObservation - uses SFINAE to deduce ResultType
    template<typename Adapter = AdapterT>
    auto handle_system_error(
        const std::system_error& e,
        const char* operation) -> 
        DegradedObservation<decltype(std::declval<Adapter>().observe_all())> {
        
        using ResultType = decltype(std::declval<Adapter>().observe_all());
        
        auto category = ProviderFailure::Category::kSystemError;
        std::string desc;
        
        // Map error codes to categories
        if (e.code() == std::errc::timed_out) {
            category = ProviderFailure::Category::kTimeout;
            desc = "Timeout in " + std::string(operation);
        } else if (e.code() == std::errc::permission_denied) {
            category = ProviderFailure::Category::kPermission;
            desc = "Permission denied in " + std::string(operation);
        } else if (e.code() == std::errc::connection_refused ||
                   e.code() == std::errc::connection_reset ||
                   e.code() == std::errc::network_down) {
            category = ProviderFailure::Category::kConnection;
            desc = "Network error in " + std::string(operation);
        } else if (e.code() == std::errc::no_such_device_or_address) {
            category = ProviderFailure::Category::kResourceExhausted;
            desc = "Resource exhausted in " + std::string(operation);
        } else {
            desc = "System error in " + std::string(operation) + ": " + e.what();
        }
        
        return DegradedObservation<ResultType>::unavailable({
            ProviderFailure{
                .provider_id = provider_id_,
                .failure_time = std::chrono::system_clock::now(),
                .category = category,
                .description = std::move(desc),
            }
        });
    }
    
private:
    std::unique_ptr<AdapterT> wrapped_;
    std::string provider_id_;
};

// ============================================================================
// IsolatedProviderFactory — Factory for creating isolated adapters
// ============================================================================

template<typename AdapterT>
std::unique_ptr<IsolatedProvider<AdapterT>> make_isolated_provider(
    std::unique_ptr<AdapterT> wrapped) {
    return std::make_unique<IsolatedProvider<AdapterT>>(std::move(wrapped));
}

template<typename AdapterT>
std::unique_ptr<IsolatedProvider<AdapterT>> make_isolated_provider(
    std::unique_ptr<AdapterT> wrapped, std::string provider_id) {
    return std::make_unique<IsolatedProvider<AdapterT>>(std::move(wrapped), std::move(provider_id));
}

}  // namespace rebuntu::adapters

// ============================================================================
// Example Usage
// ============================================================================
//
// Before (crash on failure):
//   auto adapter = make_systemd_service_discovery_adapter();
//   auto result = adapter->observe_all();  // Can throw, crash caller
//
// After (isolated):
//   auto wrapped = make_isolated_provider(
//       make_systemd_service_discovery_adapter());
//   auto result = wrapped->observe_all();
//   
//   if (result.status == core::SemanticStatus::kUnknown) {
//       // Provider unavailable, but caller didn't crash
//       for (const auto& failure : result.failures) {
//           log_error("Provider {} failed: {}", failure.provider_id, failure.description);
//       }
//   } else if (result.status == core::SemanticStatus::kCompleted) {
//       // Work done but with degradation
//       use_result(result.value);
//   } else {
//       // Full success
//       use_result(result.value);
//   }
//
// ============================================================================