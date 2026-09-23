// rebuntu::environment::authorization — Authorization & Scope Implementation (Phase 2.6)
#include <system/environment/authorization.hpp>

#include <system/environment/privilege.hpp>

namespace rebuntu::environment::authorization {

// ============================================================================
// BasicAuthorizationPolicy - Default policy implementation
// ============================================================================

AuthorizationDecisionResult BasicAuthorizationPolicy::evaluate(
    const AuthorizationRequest& request) const {
    
    // Rule 1: Root can do anything on system-scoped operations
    if (request.caller.is_root && 
        (request.scope.scope == rebuntu::environment::privilege::InstallationScope::kSystem || 
         request.target.type == TargetType::kSystem)) {
        return AuthorizationDecisionResult::allow("root user authorized for system operation");
    }
    
    // Rule 2: Non-root users cannot perform system-scoped write operations
    if (!request.caller.is_root && 
        (request.scope.scope == rebuntu::environment::privilege::InstallationScope::kSystem ||
         request.target.type == TargetType::kSystem)) {
        
        if (request.operation.op_class != OperationClass::kRead) {
            return AuthorizationDecisionResult::require_elevation(
                "system privilege required",
                "non-root user attempting system-scoped write");
        }
    }
    
    // Rule 3: Read operations are allowed by default for authenticated callers
    if (request.operation.op_class == OperationClass::kRead) {
        return AuthorizationDecisionResult::allow("read operation permitted");
    }
    
    // Rule 4: Default deny for unrecognized cases
    return AuthorizationDecisionResult::deny("no matching authorization rule");
}

// ============================================================================
// AuthorizationContext - Top-level API implementation
// ============================================================================

AuthorizationContext AuthorizationContext::current() {
    AuthorizationContext ctx;
    
    ctx.caller_ = Caller::current();
    
    // Get scope from privilege module
    auto priv_info = rebuntu::environment::privilege::discover_privilege();
    
    if (priv_info.is_root) {
        ctx.scope_.scope = rebuntu::environment::privilege::InstallationScope::kSystem;
    } else {
        ctx.scope_.scope = rebuntu::environment::privilege::InstallationScope::kUser;
        
        const char* home_env = std::getenv("HOME");
        if (home_env) {
            ctx.scope_.home_dir = home_env;
        }
    }
    
    // Note: original_uid is optional in privilege ScopeContext, so we only set if available
    if (priv_info.real_uid.has_value()) {
        ctx.scope_.original_uid = priv_info.real_uid.value();
    }
    
    return ctx;
}

AuthorizationDecisionResult AuthorizationContext::authorize(
    const RequestedOperation& operation,
    const AuthorizationTarget& target) const {
    
    BasicAuthorizationPolicy policy;
    
    AuthorizationRequest request;
    request.caller = caller_;
    request.operation = operation;
    request.target = target;
    request.scope = scope_;
    
    return policy.evaluate(request);
}

AuthorizationDecisionResult AuthorizationContext::authorize_read(
    const std::string& operation_name,
    const AuthorizationTarget& target) const {
    
    RequestedOperation op;
    op.name = operation_name;
    op.op_class = OperationClass::kRead;
    
    return authorize(op, target);
}

AuthorizationDecisionResult AuthorizationContext::authorize_write(
    const std::string& operation_name,
    const AuthorizationTarget& target) const {
    
    RequestedOperation op;
    op.name = operation_name;
    op.op_class = OperationClass::kWrite;
    
    return authorize(op, target);
}

}  // namespace rebuntu::environment::authorization