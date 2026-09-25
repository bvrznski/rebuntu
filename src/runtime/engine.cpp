// rebuntu::runtime::engine — Engine Facade Implementation (Phase 4.2)
//
// This implements the canonical runtime facade for accepting typed work
// into Rebuntu's execution machinery.

#include <runtime/engine.hpp>

namespace rebuntu::runtime::engine {

Engine::Engine() : context_{} {
    context_.created_at = std::chrono::system_clock::now();
    context_.engine_instance_id = "default";
}

Engine::Engine(EngineContext ctx) : context_(std::move(ctx)) {}

Engine::~Engine() {
    // Ensure engine is stopped on destruction
    if (state_ != EngineState::kStopped && state_ != EngineState::kCreated) {
        stop();
    }
}

EngineResult Engine::initialize() {
    std::lock_guard<std::mutex> lock(active_executions_mutex_);
    
    if (state_ != EngineState::kCreated) {
        return core::Outcome::failure("E_INVALID_STATE", "Engine already initialized or stopped");
    }
    
    state_ = EngineState::kInitializing;
    
    // Perform initialization tasks (resource allocation, etc.)
    // For now, just mark as ready
    state_ = EngineState::kReady;
    
    return core::Outcome::success();
}

EngineResult Engine::stop(std::optional<std::chrono::milliseconds> timeout) {
    (void)timeout;  // Not yet implemented - placeholder for future implementation
    
    std::lock_guard<std::mutex> lock(active_executions_mutex_);
    
    if (state_ != EngineState::kReady && state_ != EngineState::kInitializing) {
        return core::Outcome::failure("E_INVALID_STATE", "Engine not in ready state");
    }
    
    // Wait for active executions to complete
    state_ = EngineState::kStopping;
    
    // TODO: Implement proper shutdown with timeout
    
    state_ = EngineState::kStopped;
    
    return core::Outcome::success();
}

SubmissionResult Engine::submit(const WorkSubmission& submission) {
    std::lock_guard<std::mutex> lock(metrics_mutex_);
    metrics_.submissions_received++;
    
    // Check engine state
    if (state_ != EngineState::kReady) {
        SubmissionResult result;
        result.status = core::SemanticStatus::kFailure;
        return result;
    }
    
    // Check backpressure
    {
        std::lock_guard<std::mutex> active_lock(active_executions_mutex_);
        if (active_executions_ >= context_.max_concurrent_executions) {
            SubmissionResult result;
            result.status = core::SemanticStatus::kFailure;
            return result;
        }
    }
    
    // Create a unique submission ID if not provided
    std::string submission_id = submission.id.empty() 
        ? std::to_string(std::chrono::system_clock::now().time_since_epoch().count())
        : submission.id;
    
    // Determine the kind of work and route accordingly
    SubmissionResult result;
    
    switch (submission.kind) {
        case WorkSubmission::Kind::kTask:
            // For tasks, create a JobId for tracking
            result.job_id = work::JobId{submission_id};
            result.execution_id = work::ExecutionId{submission_id + ".exec1"};
            break;
            
        case WorkSubmission::Kind::kWorkflow:
            // Workflows have their own execution tracking
            result.job_id = work::JobId{submission_id};
            result.execution_id = work::ExecutionId{submission_id + ".wf_exec"};
            break;
            
        case WorkSubmission::Kind::kOperation:
            // Direct operation invocation - no job tracking needed
            result.execution_id = work::ExecutionId{submission_id};
            break;
    }
    
    {
        std::lock_guard<std::mutex> metrics_lock(metrics_mutex_);
        metrics_.submissions_accepted++;
    }
    
    // TODO: Route to dispatcher and start execution via Runner
    // This would involve:
    // 1. Creating a Job from the submission
    // 2. Using Dispatcher to select appropriate execution mechanism
    // 3. Starting a Runner with the job
    
    result.status = core::SemanticStatus::kSuccess;
    
    return result;
}

std::optional<work::JobState> Engine::get_job_state(work::JobId job_id) const {
    std::lock_guard<std::mutex> lock(job_states_mutex_);
    auto it = job_states_.find(job_id);
    if (it != job_states_.end()) {
        return it->second;
    }
    return std::nullopt;
}

EngineMetrics Engine::metrics() const {
    std::lock_guard<std::mutex> lock(metrics_mutex_);
    return metrics_;
}

void Engine::add_listener(ListenerPtr listener) {
    if (listener) {
        std::lock_guard<std::mutex> lock(listeners_mutex_);
        listeners_.push_back(listener);
    }
}

void Engine::remove_listener(const ListenerPtr& listener) {
    std::lock_guard<std::mutex> lock(listeners_mutex_);
    listeners_.erase(
        std::remove_if(listeners_.begin(), listeners_.end(),
            [&listener](const ListenerPtr& l) { return l == listener; }),
        listeners_.end());
}

// EngineBuilder implementation
EngineBuilder::EngineBuilder() {
    context_.created_at = std::chrono::system_clock::now();
    context_.engine_instance_id = "builder_default";
    context_.max_concurrent_executions = 100;
}

EngineBuilder& EngineBuilder::set_instance_id(std::string id) {
    context_.engine_instance_id = std::move(id);
    return *this;
}

EngineBuilder& EngineBuilder::set_default_timeout(std::chrono::milliseconds ms) {
    context_.default_timeout_policy.default_timeout = ms;
    return *this;
}

EngineBuilder& EngineBuilder::set_max_concurrent_executions(size_t count) {
    context_.max_concurrent_executions = count;
    return *this;
}

std::unique_ptr<Engine> EngineBuilder::build() {
    return std::make_unique<Engine>(context_);
}

}  // namespace rebuntu::runtime::engine