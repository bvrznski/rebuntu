// rebuntu::concurrency::control — Execution Concurrency Control (Phase 6.31)
//
// This establishes Rebuntu's narrow locking/serialization mechanism for preventing
// unsafe concurrent operations against the same scoped resource.
//
// Key Principle: Use narrow locking keyed by stable identity rather than a global
// execution mutex.

#pragma once

#include <system/core/contracts.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace rebuntu::concurrency {

// Forward declare LockManager for friend relationship
class LockManager;

// ============================================================================
// ResourceId — Stable identifier for a resource that can be locked
// ============================================================================

struct ResourceId {
    std::string category;     // e.g., "filesystem", "service", "package"
    std::string identifier;   // Stable identifier
    
    bool operator==(const ResourceId& other) const noexcept;
};

inline std::string to_string(const ResourceId& id) {
    return "ResourceId{" + id.category + ":" + id.identifier + "}";
}

// Hash support - defined after ResourceId
struct ResourceIdHash {
    size_t operator()(const ResourceId& id) const noexcept {
        size_t h1 = std::hash<std::string>{}(id.category);
        size_t h2 = std::hash<std::string>{}(id.identifier);
        return h1 ^ (h2 << 1);
    }
};

// ============================================================================
// LockMode — Blocking/non-blocking modes for lock acquisition
// ============================================================================

enum class LockMode {
    kBlocking,
    kNonBlocking,
    kTimeout,
};

struct LockOptions {
    LockMode mode = LockMode::kNonBlocking;
    std::optional<std::chrono::milliseconds> timeout;
    
    static LockOptions blocking() { return {LockMode::kBlocking, std::nullopt}; }
    static LockOptions non_blocking() { return {LockMode::kNonBlocking, std::nullopt}; }
    static LockOptions with_timeout(std::chrono::milliseconds ms) {
        return {LockMode::kTimeout, ms};
    }
};

// ============================================================================
// LockStatus — Result of lock acquisition
// ============================================================================

enum class LockStatus {
    kSuccess,
    kWouldBlock,
    kTimeout,
    kCancelled,
    kDeadlockDetected,
    kResourceNotFound,
    kSystemError,
};

struct LockResult {
    LockStatus status = LockStatus::kSuccess;
    std::optional<std::string> error_message;
    
    bool is_success() const { return status == LockStatus::kSuccess; }
    bool is_blocked() const { 
        return status == LockStatus::kWouldBlock || status == LockStatus::kTimeout; 
    }
};

// ============================================================================
// LockAcquisition — Represents an in-progress lock acquisition request
// ============================================================================

struct LockAcquisition {
    ResourceId resource_id;
    std::chrono::system_clock::time_point requested_at;
    
    bool is_pending() const { return false; }  // Simplified for now
};

// ============================================================================
// LockManager — Manages per-resource locks with narrow scope
// ============================================================================

class LockManager {
public:
    explicit LockManager();
    ~LockManager();
    
    LockResult acquire_lock(
        const ResourceId& resource_id,
        std::string execution_id,
        const LockOptions& options = LockOptions::non_blocking()
    );
    
    void release_lock(const ResourceId& resource_id, std::string execution_id);
    
    bool cancel_pending_acquire(std::string execution_id);
    
    std::vector<ResourceId> get_locked_resources(std::string execution_id) const;
    
    bool is_resource_locked(const ResourceId& resource_id) const;
    
    size_t get_pending_count(const ResourceId& resource_id) const;
    
    struct Metrics {
        size_t total_acquisitions = 0;
        size_t successful_acquisitions = 0;
        size_t blocked_acquisitions = 0;
        size_t timeout_acquisitions = 0;
        size_t cancelled_acquisitions = 0;
        size_t active_locks = 0;
    };
    
    Metrics metrics() const;

private:
    struct ResourceLockState {
        std::string* holder{nullptr};
        std::vector<std::shared_ptr<LockAcquisition>> queue;
        
        bool is_locked() const { return holder != nullptr; }
    };
    
    mutable std::mutex mutex_;
    std::unordered_map<ResourceId, ResourceLockState, ResourceIdHash> resource_states_;
    Metrics metrics_;
    
    // Friend for ScopedExecutionTracker to access internal state
    friend class ScopedExecutionTracker;
};

// ============================================================================
// LockGuard — RAII lock acquisition with automatic release
// ============================================================================

class LockGuard {
public:
    LockGuard(
        LockManager& manager,
        const ResourceId& resource_id,
        std::string execution_id,
        LockOptions options = LockOptions::non_blocking()
    );
    
    ~LockGuard();
    
    LockGuard(LockGuard&& other) noexcept;
    LockGuard& operator=(LockGuard&& other) noexcept;
    
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
    
    bool is_valid() const { return manager_ != nullptr; }
    void release();
    const ResourceId& resource_id() const { return resource_id_; }

private:
    LockManager* manager_;
    ResourceId resource_id_;
    std::string execution_id_;
    bool released_;
};

// ============================================================================
// ScopedExecutionTracker — Tracks active executions per resource
// ============================================================================

class ScopedExecutionTracker {
public:
    explicit ScopedExecutionTracker(LockManager& lock_manager);
    
    bool begin_execution(
        std::string execution_id,
        const std::vector<ResourceId>& resource_ids
    );
    
    void end_execution(std::string execution_id);
    
    bool has_conflicting_execution(const ResourceId& resource_id) const;
    
    std::vector<ResourceId> get_resources_with_activity() const;

private:
    LockManager& lock_manager_;
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::vector<ResourceId>> active_executions_;
};

// ============================================================================
// ExecutionConcurrencyControl — Main API for phase 6.31
// ============================================================================

class ExecutionConcurrencyControl {
public:
    explicit ExecutionConcurrencyControl();
    ~ExecutionConcurrencyControl();
    
    core::Outcome submit_operation(
        const std::string& operation_id,
        const std::vector<ResourceId>& dependent_resources,
        int max_attempts = 1,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    );
    
    bool cancel_execution(std::string execution_id);
    LockManager::Metrics metrics() const;

private:
    std::unique_ptr<LockManager> lock_manager_;
};

// ============================================================================
// ResourceId helpers
// ============================================================================

inline ResourceId make_filesystem_resource(std::string_view path) {
    ResourceId res;
    res.category = "filesystem";
    res.identifier = std::string(path);
    return res;
}

inline ResourceId make_service_resource(std::string_view service_name) {
    ResourceId res;
    res.category = "service";
    res.identifier = std::string(service_name);
    return res;
}

inline ResourceId make_package_resource(std::string_view package_name) {
    ResourceId res;
    res.category = "package";
    res.identifier = std::string(package_name);
    return res;
}

std::unique_ptr<LockManager> make_lock_manager();

}  // namespace rebuntu::concurrency
