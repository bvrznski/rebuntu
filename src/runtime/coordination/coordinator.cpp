// rebuntu::runtime::coordination::Coordinator — Execution coordination implementation (Phase 4.7)
//
// This implements the Coordinator for managing execution coordination primitives:
//   - Dependency completion tracking
//   - Resource exclusion/locks  
//   - Bounded fan-in/fan-out patterns
//   - Ordered handoff between executions

#include <runtime/coordination/context.hpp>
#include <system/core/contracts.hpp>
#include <runtime/cancellation/error.hpp>
#include <runtime/work.hpp>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <chrono>

namespace rebuntu::runtime::coordination {

// ============================================================================
// CoordinatorImpl — Internal implementation class (PIMPL pattern)
//
// The Coordinator maintains coordination state for:
//   - Pending requests: waiting for dependencies or resources
//   - Active requests: currently in progress
//   - Completed requests: finished with result
//   - Resource locks: exclusive access tracking
// ============================================================================
 
class CoordinatorImpl : public Coordinator {
public:
    explicit CoordinatorImpl(std::chrono::milliseconds default_timeout)
        : default_timeout_(default_timeout) {}
    
    ~CoordinatorImpl() override = default;  // noexcept by default matches base
    
    // Submit a coordination request
    core::Outcome submit_coordination(const CoordinationRequest& request) override {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (request.id.empty()) {
            return core::Outcome::failure("INVALID_ARGUMENT", "Coordination request ID is required");
        }
        
        // Check for duplicate request
        auto it = requests_.find(request.id);
        if (it != requests_.end() && 
            it->second.status != CoordinationResultStatus::kSuccess &&
            it->second.status != CoordinationResultStatus::kFailed) {
            return core::Outcome::failure("DUPLICATE_REQUEST", "Coordination request already exists");
        }
        
        // Record the request
        auto& record = requests_[request.id];
        record.request = request;
        record.created_at = std::chrono::system_clock::now();
        record.status = CoordinationResultStatus::kAccepted;
        
        // Notify observers
        notify_request_accepted(request);
        
        // Process based on operation type
        process_coordination(record, request.operation);
        
        return core::Outcome::success();
    }
    
    // Query the status of a pending coordination request
    std::optional<CoordinationResult> get_result(const std::string& request_id) const override {
        std::lock_guard<std::mutex> lock(mutex_);
        
        auto it = requests_.find(request_id);
        if (it == requests_.end()) {
            return std::nullopt;
        }
        
        CoordinationResult result;
        result.request_id = request_id;
        result.created_at = it->second.created_at;
        result.status = it->second.status;
        result.completed_at = it->second.completed_at;
        result.error_code = it->second.error_code;
        result.error_message = it->second.error_message;
        
        return result;
    }
    
    // Cancel a previously submitted coordination request
    core::Outcome cancel_coordination(const std::string& request_id) override {
        std::lock_guard<std::mutex> lock(mutex_);
        
        auto it = requests_.find(request_id);
        if (it == requests_.end()) {
            return core::Outcome::failure("NOT_FOUND", "Coordination request not found");
        }
        
        // Check if already completed
        if (is_complete(it->second.status)) {
            return core::Outcome::success();  // Already done
        }
        
        it->second.status = CoordinationResultStatus::kCancelled;
        it->second.completed_at = std::chrono::system_clock::now();
        
        notify_state_changed(request_id, CoordinationResultStatus::kCancelled);
        
        auto result = get_result_unlocked(it->first);
        if (result) {
            notify_coordination_completed(request_id, *result);
        }
        
        return core::Outcome::success();
    }
    
    // Add an observer for coordination events
    void add_observer(ObserverPtr observer) override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (observer) {
            observers_.push_back(observer);
        }
    }
    
    // Remove an observer
    void remove_observer(const ObserverPtr& observer) override {
        std::lock_guard<std::mutex> lock(mutex_);
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer),
            observers_.end()
        );
    }
    
private:
    struct CoordinationRecord {
        CoordinationRequest request;
        std::chrono::system_clock::time_point created_at;
        CoordinationResultStatus status = CoordinationResultStatus::kAccepted;
        std::optional<std::chrono::system_clock::time_point> completed_at;
        std::string error_code;
        std::string error_message;
    };
    
    mutable std::mutex mutex_;
    std::chrono::milliseconds default_timeout_;
    std::vector<ObserverPtr> observers_;
    std::map<std::string, CoordinationRecord> requests_;
    
    // Resource lock tracking
    std::map<std::string, std::set<std::string>> resource_holders_;
    std::map<std::string, std::set<std::string>> resource_waiters_;
    
    // Helper method declarations (must come before methods that use them)
    bool is_complete(CoordinationResultStatus status) const;
    void process_coordination(CoordinationRecord& record, CoordinationRequest::Operation op);
    void handle_wait_for(CoordinationRecord& record);
    void handle_acquire(CoordinationRecord& record);
    void handle_release(CoordinationRecord& record);
    
    // Result retrieval (helper for observer notifications)
    std::optional<CoordinationResult> get_result_unlocked(const std::string& request_id) const;
    
    // Observer notification helpers
    void notify_request_accepted(const CoordinationRequest& request);
    void notify_state_changed(const std::string& request_id, CoordinationResultStatus status);
    void notify_coordination_completed(const std::string& request_id, const CoordinationResult& result);
};

// ============================================================================
// CoordinatorImpl method implementations (after class definition)
// ============================================================================

bool CoordinatorImpl::is_complete(CoordinationResultStatus status) const {
    return status == CoordinationResultStatus::kSuccess ||
           status == CoordinationResultStatus::kFailed ||
           status == CoordinationResultStatus::kTimedOut ||
           status == CoordinationResultStatus::kCancelled;
}

std::optional<CoordinationResult> CoordinatorImpl::get_result_unlocked(const std::string& request_id) const {
    auto it = requests_.find(request_id);
    if (it == requests_.end()) return std::nullopt;
    
    CoordinationResult result;
    result.request_id = request_id;
    result.created_at = it->second.created_at;
    result.status = it->second.status;
    result.completed_at = it->second.completed_at;
    result.error_code = it->second.error_code;
    result.error_message = it->second.error_message;
    return result;
}

void CoordinatorImpl::notify_request_accepted(const CoordinationRequest& request) {
    for (const auto& observer : observers_) {
        if (observer) observer->on_request_accepted(request);
    }
}

void CoordinatorImpl::notify_state_changed(const std::string& request_id, CoordinationResultStatus status) {
    for (const auto& observer : observers_) {
        if (observer) observer->on_state_changed(request_id, status);
    }
}

void CoordinatorImpl::notify_coordination_completed(const std::string& request_id, const CoordinationResult& result) {
    for (const auto& observer : observers_) {
        if (observer) observer->on_coordination_completed(request_id, result);
    }
}

void CoordinatorImpl::process_coordination(CoordinationRecord& record, CoordinationRequest::Operation op) {
    switch (op) {
        case CoordinationRequest::Operation::kWaitFor:
            handle_wait_for(record);
            break;
        case CoordinationRequest::Operation::kAcquire:
            handle_acquire(record);
            break;
        case CoordinationRequest::Operation::kRelease:
            handle_release(record);
            break;
        default:
            record.status = CoordinationResultStatus::kSuccess;
            record.completed_at = std::chrono::system_clock::now();
            notify_state_changed(record.request.id, CoordinationResultStatus::kSuccess);
            auto result = get_result_unlocked(record.request.id);
            if (result) notify_coordination_completed(record.request.id, *result);
            break;
    }
}

void CoordinatorImpl::handle_wait_for(CoordinationRecord& record) {
    bool all_complete = true;
    
    for (const auto& dep_id : record.request.dependency_ids) {
        std::string dep_request_id = "dep_" + dep_id.value;
        auto dep_it = requests_.find(dep_request_id);
        
        if (dep_it == requests_.end()) {
            all_complete = false;
            break;
        }
        
        if (!is_complete(dep_it->second.status)) {
            all_complete = false;
            break;
        }
        
        if (dep_it->second.status != CoordinationResultStatus::kSuccess) {
            record.status = CoordinationResultStatus::kFailed;
            record.error_code = "DEPENDENCY_FAILED";
            record.error_message = "Dependency " + dep_id.value + " did not succeed";
            record.completed_at = std::chrono::system_clock::now();
            
            notify_state_changed(record.request.id, CoordinationResultStatus::kFailed);
            auto result = get_result_unlocked(record.request.id);
            if (result) notify_coordination_completed(record.request.id, *result);
            return;
        }
    }
    
    {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (all_complete) {
            record.status = CoordinationResultStatus::kSuccess;
            record.completed_at = std::chrono::system_clock::now();
            notify_state_changed(record.request.id, CoordinationResultStatus::kSuccess);
            auto result = get_result_unlocked(record.request.id);
            if (result) notify_coordination_completed(record.request.id, *result);
        } else {
            record.status = CoordinationResultStatus::kPending;
            notify_state_changed(record.request.id, CoordinationResultStatus::kPending);
        }
    }
}

void CoordinatorImpl::handle_acquire(CoordinationRecord& record) {
    const std::string& resource_id = record.request.target_id;
    
    auto it = resource_holders_.find(resource_id);
    if (it == resource_holders_.end() || it->second.empty()) {
        // Resource available, grant the lock
        resource_holders_[resource_id].insert(record.request.id);
        record.status = CoordinationResultStatus::kSuccess;
        record.completed_at = std::chrono::system_clock::now();
        
        notify_state_changed(record.request.id, CoordinationResultStatus::kSuccess);
        auto result = get_result_unlocked(record.request.id);
        if (result) notify_coordination_completed(record.request.id, *result);
    } else {
        // Resource in use - add to waiters
        resource_waiters_[resource_id].insert(record.request.id);
        record.status = CoordinationResultStatus::kPending;
        
        notify_state_changed(record.request.id, CoordinationResultStatus::kPending);
    }
}

void CoordinatorImpl::handle_release(CoordinationRecord& record) {
    const std::string& resource_id = record.request.target_id;
    
    auto it = resource_holders_.find(resource_id);
    if (it != resource_holders_.end()) {
        it->second.erase(record.request.id);
        
        // Check if there are waiters for this resource
        auto waiter_it = resource_waiters_.find(resource_id);
        if (waiter_it != resource_waiters_.end() && !waiter_it->second.empty()) {
            // Grant to first waiter
            std::string next_holder = *waiter_it->second.begin();
            waiter_it->second.erase(waiter_it->second.begin());
            
            auto holder_record = requests_.find(next_holder);
            if (holder_record != requests_.end() && 
                holder_record->second.status == CoordinationResultStatus::kPending) {
                holder_record->second.status = CoordinationResultStatus::kSuccess;
                holder_record->second.completed_at = std::chrono::system_clock::now();
                
                resource_holders_[resource_id].insert(next_holder);
                
                notify_state_changed(next_holder, CoordinationResultStatus::kSuccess);
                auto result = get_result_unlocked(next_holder);
                if (result) notify_coordination_completed(next_holder, *result);
            }
        }
        
        record.status = CoordinationResultStatus::kSuccess;
        record.completed_at = std::chrono::system_clock::now();
    } else {
        record.status = CoordinationResultStatus::kFailed;
        record.error_code = "RESOURCE_NOT_HELD";
        record.error_message = "Resource is not currently held by this coordinator";
    }
    
    notify_state_changed(record.request.id, record.status);
    auto result = get_result_unlocked(record.request.id);
    if (result) notify_coordination_completed(record.request.id, *result);
}

// ============================================================================
// CoordinatorBuilder
// ============================================================================

CoordinatorBuilder::CoordinatorBuilder() {
    default_timeout_ = std::chrono::milliseconds(30000);  // Default 30 seconds
}

CoordinatorBuilder& CoordinatorBuilder::set_default_timeout(std::chrono::milliseconds ms) {
    default_timeout_ = ms;
    return *this;
}

CoordinatorBuilder& CoordinatorBuilder::add_observer(CoordinatorBuilder::ObserverPtr observer) {
    if (observer) {
        observers_.push_back(observer);
    }
    return *this;
}

CoordinatorBuilder& CoordinatorBuilder::set_max_concurrent_coordination(size_t count) {
    max_concurrent_coordination_ = count;
    return *this;
}

std::unique_ptr<Coordinator> CoordinatorBuilder::build() {
    auto coordinator = std::make_unique<CoordinatorImpl>(default_timeout_);
    
    // Add registered observers
    for (const auto& obs : observers_) {
        if (obs) coordinator->add_observer(obs);
    }
    
    return coordinator;
}

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<Coordinator> make_coordinator() {
    return CoordinatorBuilder{}.build();
}

std::unique_ptr<Coordinator> make_coordinator_with_timeout(std::chrono::milliseconds timeout) {
    return CoordinatorBuilder{}
        .set_default_timeout(timeout)
        .build();
}

}  // namespace rebuntu::runtime::coordination