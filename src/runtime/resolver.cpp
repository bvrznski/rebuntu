// rebuntu::runtime::resolver — Runtime Resolution Implementation (Phase 4.8)

#include <runtime/resolver.hpp>
#include <runtime/contracts.hpp>

namespace rebuntu::runtime::resolver {

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<Resolver> make_resolver() {
    return std::make_unique<InMemoryResolver>();
}

// ============================================================================
// InMemoryResolver Implementation
// ============================================================================

InMemoryResolver::InMemoryResolver() = default;

InMemoryResolver::~InMemoryResolver() = default;

void InMemoryResolver::add_task(const work::Task& task) {
    tasks_[task.id.value] = task;
    
    // Record in resolution history
    ResolutionResult result;
    result.status = rebuntu::core::SemanticStatus::kSuccess;
    result.candidate.id = task.id.value;
    result.candidate.title = task.title;
    result.candidate.description = task.description;
    result.candidate.kind = ResolutionCandidate::Kind::kTask;
    result.resolved_scope = "system";
    
    resolution_history_.push_back(result);
}

void InMemoryResolver::add_operation(const rebuntu::core::OperationDefinition& op_def) {
    operations_[op_def.id] = op_def;
    
    // Record in resolution history
    ResolutionResult result;
    result.status = rebuntu::core::SemanticStatus::kSuccess;
    result.candidate.id = op_def.id;
    result.candidate.title = op_def.title;
    result.candidate.description = op_def.description;
    result.candidate.kind = ResolutionCandidate::Kind::kOperation;
    result.resolved_scope = "system";
    
    resolution_history_.push_back(result);
}

ResolutionResult InMemoryResolver::resolve_task(
    const std::string& id, 
    const ResolutionContext& ctx) const {
    
    (void)ctx;  // Context not used for basic lookup
    
    auto it = tasks_.find(id);
    if (it == tasks_.end()) {
        ResolutionResult result;
        result.status = rebuntu::core::SemanticStatus::kUnknown;
        RejectionReason rr;
        rr.category = RejectionReason::Category::kNotFound;
        rr.code = "E_NOT_FOUND";
        rr.message = "Task not found: " + id;
        result.rejections.push_back(rr);
        return result;
    }
    
    ResolutionResult result;
    result.status = rebuntu::core::SemanticStatus::kSuccess;
    result.candidate.id = it->second.id.value;
    result.candidate.title = it->second.title;
    result.candidate.description = it->second.description;
    result.candidate.kind = ResolutionCandidate::Kind::kTask;
    result.resolved_scope = "system";
    
    // Record in history
    resolution_history_.push_back(result);
    
    return result;
}

ResolutionResult InMemoryResolver::resolve_operation(
    const std::string& id, 
    const ResolutionContext& ctx) const {
    
    (void)ctx;  // Context not used for basic lookup
    
    auto it = operations_.find(id);
    if (it == operations_.end()) {
        ResolutionResult result;
        result.status = rebuntu::core::SemanticStatus::kUnknown;
        RejectionReason rr;
        rr.category = RejectionReason::Category::kNotFound;
        rr.code = "E_NOT_FOUND";
        rr.message = "Operation not found: " + id;
        result.rejections.push_back(rr);
        return result;
    }
    
    ResolutionResult result;
    result.status = rebuntu::core::SemanticStatus::kSuccess;
    result.candidate.id = it->second.id;
    result.candidate.title = it->second.title;
    result.candidate.description = it->second.description;
    result.candidate.kind = ResolutionCandidate::Kind::kOperation;
    result.resolved_scope = "system";
    
    // Record in history
    resolution_history_.push_back(result);
    
    return result;
}

ResolutionResult InMemoryResolver::resolve(
    const std::string& id, 
    const ResolutionContext& ctx) {
    
    (void)ctx;  // Context not used for basic lookup
    
    // Try to resolve as a task first
    auto task_result = resolve_task(id, ctx);
    if (task_result.succeeded()) {
        return task_result;
    }
    
    // If not found in tasks, try operations
    auto op_result = resolve_operation(id, ctx);
    if (op_result.succeeded()) {
        return op_result;
    }
    
    // Combine rejections from both attempts
    ResolutionResult result;
    result.status = rebuntu::core::SemanticStatus::kUnknown;
    result.rejections.insert(
        result.rejections.end(), 
        task_result.rejections.begin(), 
        task_result.rejections.end()
    );
    result.rejections.insert(
        result.rejections.end(), 
        op_result.rejections.begin(), 
        op_result.rejections.end()
    );
    
    // Record final attempt in history
    resolution_history_.push_back(result);
    
    return result;
}

std::vector<ResolutionCandidate> InMemoryResolver::list_candidates(
    std::optional<ResolutionCandidate::Kind> kind_filter,
    std::optional<std::string>) const {
    
    std::vector<ResolutionCandidate> candidates;
    
    // Add tasks
    for (const auto& [id, task] : tasks_) {
        if (kind_filter && *kind_filter != ResolutionCandidate::Kind::kTask) continue;
        
        ResolutionCandidate candidate;
        candidate.id = task.id.value;
        candidate.title = task.title;
        candidate.description = task.description;
        candidate.kind = ResolutionCandidate::Kind::kTask;
        candidates.push_back(candidate);
    }
    
    // Add operations
    for (const auto& [id, op] : operations_) {
        if (kind_filter && *kind_filter != ResolutionCandidate::Kind::kOperation) continue;
        
        ResolutionCandidate candidate;
        candidate.id = op.id;
        candidate.title = op.title;
        candidate.description = op.description;
        candidate.kind = ResolutionCandidate::Kind::kOperation;
        candidates.push_back(candidate);
    }
    
    return candidates;
}

std::vector<ResolutionResult> InMemoryResolver::get_resolution_history() const {
    return resolution_history_;
}

}  // namespace rebuntu::runtime::resolver