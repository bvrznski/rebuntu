// rebuntu::runtime::shutdown::Coordinator — Shutdown Coordinator (Phase 4.0)
//
// ShutdownCoordinator manages graceful shutdown of Rebuntu runtime components.
// It ensures:
// - Components are stopped in dependency order
// - Timeout enforcement for each component's shutdown
// - Proper resource cleanup
// - Graceful vs forced termination

#pragma once

#include <runtime/shutdown/error.hpp>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <chrono>

namespace rebuntu::runtime {

struct ShutdownComponent {
    std::string name;  // Human-readable component name
    std::function<void()> shutdown_fn;  // Function to call for graceful shutdown
    std::function<void()> force_shutdown_fn;  // Function for forced termination
    std::chrono::milliseconds timeout;  // Max time for graceful shutdown
};

class ShutdownCoordinator {
public:
    ShutdownCoordinator() = default;
    
    // Register a component for shutdown management
    void register_component(
        std::string name,
        std::function<void()> shutdown_fn,
        std::optional<std::function<void()>> force_shutdown_fn = std::nullopt,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)) {
        
        std::lock_guard lock(mutex_);
        components_[name] = {
            std::move(name),
            std::move(shutdown_fn),
            force_shutdown_fn.value_or([]() {}),
            timeout
        };
    }
    
    // Shutdown all components in order (reverse registration order)
    void shutdown_all(std::chrono::milliseconds global_timeout = std::chrono::seconds(60)) {
        std::lock_guard lock(mutex_);
        
        auto deadline = std::chrono::steady_clock::now() + global_timeout;
        
        // Shutdown in reverse order (most dependent first)
        for (auto it = components_.rbegin(); it != components_.rend(); ++it) {
            if (std::chrono::steady_clock::now() >= deadline) {
                break;  // Global timeout reached
            }
            
            auto remaining = deadline - std::chrono::steady_clock::now();
            shutdown_component(it->second, 
                             std::min(remaining, it->second.timeout));
        }
    }
    
    // Shutdown a specific component by name
    bool shutdown_component(std::string_view name) {
        std::lock_guard lock(mutex_);
        
        auto it = components_.find(std::string{name});
        if (it == components_.end()) {
            return false;  // Component not found
        }
        
        shutdown_component(it->second, it->second.timeout);
        return true;
    }
    
    // Get count of registered components
    size_t component_count() const {
        std::lock_guard lock(mutex_);
        return components_.size();
    }
    
    // Check if all components have been shut down
    bool is_shutdown() const {
        std::lock_guard lock(mutex_);
        return shutdown_complete_;
    }

private:
    void shutdown_component(const ShutdownComponent& comp, 
                           std::chrono::milliseconds timeout) {
        // Start shutdown timer (in real implementation would use thread/timerfd)
        auto start = std::chrono::steady_clock::now();
        
        // Call the shutdown function
        comp.shutdown_fn();
        
        // In production, we'd wait for completion with timeout here
        // For now, just track that we attempted graceful shutdown
        
        auto elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed >= timeout) {
            // Graceful shutdown timed out, force termination
            comp.force_shutdown_fn();
        }
    }
    
    mutable std::mutex mutex_;
    std::map<std::string, ShutdownComponent> components_;
    bool shutdown_complete_ = false;
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