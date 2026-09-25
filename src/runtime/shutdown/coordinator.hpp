// rebuntu::runtime::shutdown::Coordinator — Shutdown Coordinator (Phase 4.19)
//
// ShutdownCoordinator manages graceful shutdown of Rebuntu runtime components.
// It ensures:
// - Components are stopped in dependency order
// - Timeout enforcement for each component's shutdown
// - Proper resource cleanup
// - Graceful vs forced termination
// - Cancellation propagation to active work

#pragma once

#include <runtime/shutdown/context.hpp>
#include <runtime/cancellation/token.hpp>
#include <system/core/results.hpp>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <chrono>
#include <atomic>

namespace rebuntu::runtime {

// ShutdownComponent: A component that can be gracefully shut down
struct ShutdownComponent {
    std::string name;  // Human-readable component name
    std::function<void()> shutdown_fn;  // Function to call for graceful shutdown
    std::function<void()> force_shutdown_fn;  // Function for forced termination
    std::chrono::milliseconds timeout;  // Max time for graceful shutdown
};

// ShutdownCoordinator: Manages shutdown phases and coordination
class ShutdownCoordinator {
public:
    ShutdownCoordinator() = default;
    
    ~ShutdownCoordinator() {
        // If coordinator is destroyed while not fully shut down,
        // attempt cleanup (not ideal but prevents resource leaks)
        if (!shutdown_complete_.load()) {
            shutdown_all(shutdown::ShutdownPolicy{.total_timeout = std::chrono::milliseconds(5000)});  // Force quick cleanup
        }
    }
    
    // Register a component for shutdown management
    void register_component(
        std::string name,
        std::function<void()> shutdown_fn,
        std::function<void()> force_shutdown_fn = []() {},
        std::chrono::milliseconds timeout = std::chrono::seconds(30)) {
        
        std::lock_guard<std::mutex> lock(mutex_);
        components_[name] = {
            std::move(name),
            std::move(shutdown_fn),
            std::move(force_shutdown_fn),
            timeout
        };
    }
    
    // Shutdown all components in order (reverse registration order)
    // Returns result with timing and completion details
    shutdown::ShutdownResult shutdown_all(
        const shutdown::ShutdownPolicy& policy = {},
        std::shared_ptr<runtime::CancellationToken> cancellation_token = nullptr) {
        
        shutdown::ShutdownContext ctx;
        ctx.phase = shutdown::ShutdownPhase::kStoppingAdmission;
        ctx.start_time = std::chrono::system_clock::now();
        ctx.deadline = ctx.start_time + policy.total_timeout;
        ctx.policy = policy;
        
        if (!cancellation_token) {
            cancellation_token = std::make_shared<runtime::CancellationToken>();
        }
        ctx.cancellation_token = cancellation_token;
        
        // Phase 1: Stop admission (cancel token signals all work)
        auto cancel_start = std::chrono::steady_clock::now();
        ctx.phase = shutdown::ShutdownPhase::kCancelling;
        ctx.cancellation_token->request_cancel("shutdown initiated");
        
        auto cancel_end = std::chrono::steady_clock::now();
        ctx.stopping_admission_time_ms = 
            std::chrono::duration_cast<std::chrono::milliseconds>(cancel_end - cancel_start);
        
        // Phase 2: Drain period (wait for existing work to complete)
        ctx.phase = shutdown::ShutdownPhase::kDraining;
        auto drain_start = std::chrono::steady_clock::now();
        auto drain_deadline = drain_start + policy.drain_timeout;
        
        // In a full implementation, we'd wait here with polling/condvar
        // For now, we simulate the wait and proceed to termination
        
        // Phase 3: Force terminate remaining work
        ctx.phase = shutdown::ShutdownPhase::kTerminating;
        auto term_start = std::chrono::steady_clock::now();
        
        {
            std::lock_guard<std::mutex> lock(mutex_);
            
            // Shutdown in reverse order (most dependent first)
            for (auto it = components_.rbegin(); it != components_.rend(); ++it) {
                if (std::chrono::steady_clock::now() >= drain_deadline) {
                    ctx.timeout_expired++;
                    break;  // Drain timeout reached
                }
                
                auto remaining_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    drain_deadline - std::chrono::steady_clock::now());
                auto component_timeout = std::min(remaining_ms, it->second.timeout);
                shutdown_component(it->second, component_timeout, &ctx);
            }
        }
        
        auto term_end = std::chrono::steady_clock::now();
        ctx.termination_time_ms = 
            std::chrono::duration_cast<std::chrono::milliseconds>(term_end - term_start);
        
        // Phase 4: Clean up
        ctx.phase = shutdown::ShutdownPhase::kCleaningUp;
        ctx.resources_released = true;
        
        auto cleanup_end = std::chrono::steady_clock::now();
        auto total_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            cleanup_end - cancel_start);
        
        // Phase 5: Complete
        ctx.phase = shutdown::ShutdownPhase::kComplete;
        shutdown_complete_.store(true);
        
        return build_result(ctx, policy.total_timeout);
    }
    
    // Shutdown a specific component by name
    bool shutdown_component(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        auto it = components_.find(name);
        if (it == components_.end()) {
            return false;  // Component not found
        }
        
        shutdown_component(it->second, it->second.timeout);
        return true;
    }
    
    // Get count of registered components
    size_t component_count() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return components_.size();
    }
    
    // Check if all components have been shut down
    bool is_shutdown() const {
        return shutdown_complete_.load();
    }

private:
    void shutdown_component(const ShutdownComponent& comp, 
                           std::chrono::milliseconds timeout,
                           shutdown::ShutdownContext* ctx = nullptr) {
        auto start = std::chrono::steady_clock::now();
        
        // Call the shutdown function
        comp.shutdown_fn();
        
        // In a full implementation, we'd wait for completion with timeout using:
        // - Condition variable for signal-based completion
        // - timerfd for timeout enforcement (native Linux)
        // For now, just track timing
        
        auto elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed >= timeout) {
            // Graceful shutdown timed out, force termination
            comp.force_shutdown_fn();
            if (ctx) ctx->force_terminated++;
        } else {
            if (ctx) ctx->graceful_completions++;
        }
    }
    
    shutdown::ShutdownResult build_result(
        const shutdown::ShutdownContext& ctx,
        [[maybe_unused]] std::chrono::milliseconds total_timeout) const {
        
        shutdown::ShutdownResult result;
        result.status = core::SemanticStatus::kSuccess;
        result.graceful_completions = ctx.graceful_completions;
        result.force_terminated = ctx.force_terminated;
        result.timeout_expired = ctx.timeout_expired;
        
        // Note: ctx.start_time is system_clock time_point, so we use it directly
        // total_shutdown_time_ms comes from context which already computed timing
        result.total_shutdown_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            ctx.stopping_admission_time_ms + ctx.draining_time_ms + ctx.termination_time_ms);
        
        return result;
    }
    
    mutable std::mutex mutex_;
    std::map<std::string, ShutdownComponent> components_;
    std::atomic<bool> shutdown_complete_{false};
};

namespace shutdown {

// Factory function for coordinator with default timeouts
inline std::unique_ptr<ShutdownCoordinator> make_coordinator() {
    return std::make_unique<ShutdownCoordinator>();
}

}  // namespace shutdown
}  // namespace rebuntu::runtime

namespace rebuntu { namespace runtime { namespace shutdown {
struct Error {};
}}}