// rebuntu::concurrency::control — Execution Concurrency Control Implementation (Phase 6.31)
//
// Implements narrow locking/serialization keyed by stable resource identity.

#include <system/concurrency/control.hpp>
#include <chrono>
#include <optional>
#include <memory>
#include <string_view>

namespace rebuntu::concurrency {

// ============================================================================
// LockManager implementation
// ============================================================================

LockManager::LockManager() {
    // Initialize metrics to zero
}

LockManager::~LockManager() = default;

LockResult LockManager::acquire_lock(
    const ResourceId& resource_id,
    std::string execution_id,
    const LockOptions& options
) {
    std::unique_lock<std::mutex> lock(mutex_);
    
    Metrics& m = metrics_;
    ++m.total_acquisitions;
    
    auto it = resource_states_.find(resource_id);
    
    // Create new state if not exists
    if (it == resource_states_.end()) {
        ResourceLockState state;
        state.holder = nullptr;
        resource_states_[resource_id] = state;
        it = resource_states_.find(resource_id);
    }
    
    ResourceLockState& state = it->second;
    
    // If resource is not locked, acquire immediately
    if (!state.is_locked()) {
        auto holder_ptr = std::make_unique<std::string>(std::move(execution_id));
        state.holder = holder_ptr.get();
        ++m.successful_acquisitions;
        return LockResult{LockStatus::kSuccess, std::nullopt};
    }
    
    // Resource is already locked by another execution
    if (options.mode == LockMode::kNonBlocking) {
        ++m.blocked_acquisitions;
        return LockResult{LockStatus::kWouldBlock, std::nullopt};
    }
    
    // Blocking mode - need to wait (simplified: just queue for now)
    auto acquisition = std::make_shared<LockAcquisition>();
    acquisition->resource_id = resource_id;
    acquisition->requested_at = std::chrono::system_clock::now();
    state.queue.push_back(acquisition);
    
    ++m.blocked_acquisitions;
    
    // For this simple implementation, we return would_block for blocking mode too
    // A full implementation would use condition_variable for actual waiting
    return LockResult{LockStatus::kWouldBlock, std::nullopt};
}

void LockManager::release_lock(const ResourceId& resource_id, std::string execution_id) {
    std::unique_lock<std::mutex> lock(mutex_);
    
    auto it = resource_states_.find(resource_id);
    if (it == resource_states_.end()) {
        return;
    }
    
    ResourceLockState& state = it->second;
    
    // Only the holder can release
    if (!state.holder || *state.holder != execution_id) {
        return;
    }
    
    // Clear holder
    state.holder = nullptr;
}

bool LockManager::cancel_pending_acquire(std::string execution_id) {
    std::unique_lock<std::mutex> lock(mutex_);
    
    bool cancelled = false;
    
    for (auto& [resource_id, state] : resource_states_) {
        auto it = std::remove_if(state.queue.begin(), state.queue.end(),
            [&execution_id](const std::shared_ptr<LockAcquisition>& /*acq*/) {
                // Simplified: cancel all pending acquisitions
                return true;
            });
        
        if (it != state.queue.end()) {
            state.queue.erase(it, state.queue.end());
            cancelled = true;
        }
    }
    
    if (cancelled) {
        ++metrics_.cancelled_acquisitions;
    }
    
    return cancelled;
}

std::vector<ResourceId> LockManager::get_locked_resources(std::string execution_id) const {
    std::unique_lock<std::mutex> lock(mutex_);
    
    std::vector<ResourceId> result;
    
    for (const auto& [resource_id, state] : resource_states_) {
        if (state.holder && *state.holder == execution_id) {
            result.push_back(resource_id);
        }
    }
    
    return result;
}

bool LockManager::is_resource_locked(const ResourceId& resource_id) const {
    std::unique_lock<std::mutex> lock(mutex_);
    
    auto it = resource_states_.find(resource_id);
    if (it == resource_states_.end()) {
        return false;
    }
    
    return it->second.is_locked();
}

size_t LockManager::get_pending_count(const ResourceId& resource_id) const {
    std::unique_lock<std::mutex> lock(mutex_);
    
    auto it = resource_states_.find(resource_id);
    if (it == resource_states_.end()) {
        return 0;
    }
    
    return it->second.queue.size();
}

LockManager::Metrics LockManager::metrics() const {
    std::unique_lock<std::mutex> lock(mutex_);
    return metrics_;
}

// ============================================================================
// LockGuard implementation
// ============================================================================

LockGuard::LockGuard(
    LockManager& manager,
    const ResourceId& resource_id,
    std::string execution_id,
    LockOptions options
) : manager_{&manager},
    resource_id_{resource_id},
    execution_id_(std::move(execution_id)),
    released_{false} {
    
    auto result = manager_->acquire_lock(resource_id, execution_id_, options);
    
    if (!result.is_success()) {
        // Mark as invalid - lock not acquired
        manager_ = nullptr;
    }
}

LockGuard::~LockGuard() {
    if (manager_ && !released_) {
        manager_->release_lock(resource_id_, execution_id_);
    }
}

LockGuard::LockGuard(LockGuard&& other) noexcept
    : manager_{other.manager_},
      resource_id_(std::move(other.resource_id_)),
      execution_id_(std::move(other.execution_id_)),
      released_{other.released_} {
    
    other.manager_ = nullptr;
    other.released_ = true;
}

LockGuard& LockGuard::operator=(LockGuard&& other) noexcept {
    if (this != &other) {
        // Release current lock
        if (manager_ && !released_) {
            manager_->release_lock(resource_id_, execution_id_);
        }
        
        // Move from other
        manager_ = other.manager_;
        resource_id_ = std::move(other.resource_id_);
        execution_id_ = std::move(other.execution_id_);
        released_ = other.released_;
        
        // Clear other
        other.manager_ = nullptr;
        other.released_ = true;
    }
    
    return *this;
}

void LockGuard::release() {
    if (manager_ && !released_) {
        manager_->release_lock(resource_id_, execution_id_);
        released_ = true;
    }
}

// ============================================================================
// ScopedExecutionTracker implementation
// ============================================================================

ScopedExecutionTracker::ScopedExecutionTracker(LockManager& lock_manager)
    : lock_manager_{lock_manager} {}

bool ScopedExecutionTracker::begin_execution(
    std::string execution_id,
    const std::vector<ResourceId>& resource_ids
) {
    // Note: This is a simplified implementation that just tracks resources
    // In a full implementation, we would actually acquire locks first
    
    std::unique_lock<std::mutex> lock(mutex_);
    
    // Check if any of these resources are already locked by another execution
    for (const auto& resource_id : resource_ids) {
        auto it = lock_manager_.resource_states_.find(resource_id);
        if (it != lock_manager_.resource_states_.end()) {
            const auto& state = it->second;
            if (state.is_locked() && state.holder && *state.holder != execution_id) {
                return false;  // Conflict detected
            }
        }
    }
    
    // No conflicts - track this execution
    active_executions_[execution_id] = resource_ids;
    return true;
}

void ScopedExecutionTracker::end_execution(std::string execution_id) {
    std::unique_lock<std::mutex> lock(mutex_);
    
    auto it = active_executions_.find(execution_id);
    if (it != active_executions_.end()) {
        // Release all locks for this execution
        for (const auto& resource_id : it->second) {
            lock_manager_.release_lock(resource_id, execution_id);
        }
        
        active_executions_.erase(it);
    }
}

bool ScopedExecutionTracker::has_conflicting_execution(const ResourceId& resource_id) const {
    std::unique_lock<std::mutex> lock(mutex_);
    
    for (const auto& [exec_id, resources] : active_executions_) {
        if (std::find(resources.begin(), resources.end(), resource_id) != resources.end()) {
            return true;
        }
    }
    
    return false;
}

std::vector<ResourceId> ScopedExecutionTracker::get_resources_with_activity() const {
    std::unique_lock<std::mutex> lock(mutex_);
    
    std::vector<ResourceId> result;
    
    for (const auto& [exec_id, resources] : active_executions_) {
        for (const auto& resource_id : resources) {
            if (std::find(result.begin(), result.end(), resource_id) == result.end()) {
                result.push_back(resource_id);
            }
        }
    }
    
    return result;
}

// ============================================================================
// ExecutionConcurrencyControl implementation
// ============================================================================

ExecutionConcurrencyControl::ExecutionConcurrencyControl()
    : lock_manager_{make_lock_manager()} {}

ExecutionConcurrencyControl::~ExecutionConcurrencyControl() = default;

core::Outcome ExecutionConcurrencyControl::submit_operation(
    const std::string& /*operation_id*/,
    const std::vector<ResourceId>& dependent_resources,
    int /*max_attempts*/,
    std::optional<std::chrono::milliseconds> timeout
) {
    // Generate execution ID (simplified: timestamp-based)
    auto exec_id = "exec_" + std::to_string(
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count()
    );
    
    // Try to acquire locks for all dependent resources
    LockOptions options;
    if (timeout.has_value()) {
        options = LockOptions::with_timeout(*timeout);
    }
    
    for (const auto& resource_id : dependent_resources) {
        auto result = lock_manager_->acquire_lock(resource_id, exec_id, options);
        
        if (!result.is_success()) {
            // Could not acquire lock - operation would conflict
            return core::Outcome::failure(
                "E_CONCURRENT_MODIFICATION",
                "Operation conflicts with active execution on resource: " + to_string(resource_id)
            );
        }
    }
    
    // Execute the operation (placeholder for actual implementation)
    // In a real implementation, this would:
    // 1. Record execution state
    // 2. Execute via appropriate provider
    // 3. Verify results
    // 4. Release locks
    
    core::Outcome result = core::Outcome::success();
    
    // Release all acquired locks
    for (const auto& resource_id : dependent_resources) {
        lock_manager_->release_lock(resource_id, exec_id);
    }
    
    return result;
}

bool ExecutionConcurrencyControl::cancel_execution(std::string execution_id) {
    return lock_manager_->cancel_pending_acquire(execution_id);
}

LockManager::Metrics ExecutionConcurrencyControl::metrics() const {
    return lock_manager_->metrics();
}

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<LockManager> make_lock_manager() {
    return std::make_unique<LockManager>();
}

// ============================================================================
// ResourceId implementation
// ============================================================================

bool ResourceId::operator==(const ResourceId& other) const noexcept {
    return category == other.category && identifier == other.identifier;
}


}  // namespace rebuntu::concurrency
