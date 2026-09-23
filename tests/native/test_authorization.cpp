// Rebuntu — Authorization & Scope Tests (Phase 2.6)
//
// Test the authorization model:
//   - Decision types
//   - Caller identity
//   - Scope context
//   - Policy evaluation

#include <observation/environment/authorization.hpp>

#include <iostream>
#include <cstdlib>
#include <unistd.h>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

int main() {
    using rebuntu::environment::authorization::AuthorizationDecision;
    using rebuntu::environment::authorization::to_string;
    using rebuntu::environment::authorization::Caller;
    using rebuntu::environment::authorization::ScopeContext;
    using rebuntu::environment::authorization::BasicAuthorizationPolicy;
    using rebuntu::environment::authorization::AuthorizationContext;
    
    std::cout << "Testing authorization and scope...\\n";
    
    // Test 1: AuthorizationDecision string conversion
    {
        CHECK(std::string(to_string(AuthorizationDecision::kAllow)) == "allow");
        CHECK(std::string(to_string(AuthorizationDecision::kDeny)) == "deny");
        CHECK(std::string(to_string(AuthorizationDecision::kRequireElevation)) == "require-elevation");
        CHECK(std::string(to_string(AuthorizationDecision::kRequireConfirmation)) == "require-confirmation");
        CHECK(std::string(to_string(AuthorizationDecision::kInsufficientInformation)) == "insufficient-information");
    }
    
    // Test 2: Caller current() captures process identity
    {
        auto caller = Caller::current();
        std::cout << "Caller UID: " << caller.uid << ", EUID: " << caller.euid << "\\n";
        CHECK(caller.euid == geteuid());
    }
    
    // Test 3: ScopeContext default values
    {
        ScopeContext ctx;
        CHECK(ctx.scope == rebuntu::environment::privilege::InstallationScope::kUser);
    }
    
    // Test 4: BasicAuthorizationPolicy - allows read operations
    {
        BasicAuthorizationPolicy policy;
        
        rebuntu::environment::authorization::RequestedOperation op;
        op.name = "read_config";
        op.op_class = rebuntu::environment::authorization::OperationClass::kRead;
        
        rebuntu::environment::authorization::AuthorizationTarget target;
        target.type = rebuntu::environment::authorization::TargetType::kSystem;
        
        auto result = policy.evaluate({
            Caller::current(),
            op,
            target,
            ScopeContext{}
        });
        
        CHECK(result.decision == AuthorizationDecision::kAllow);
    }
    
    // Test 5: BasicAuthorizationPolicy - default deny for unrecognized
    {
        BasicAuthorizationPolicy policy;
        
        rebuntu::environment::authorization::RequestedOperation op;
        op.name = "unknown_operation";
        op.op_class = rebuntu::environment::authorization::OperationClass::kManage;
        
        rebuntu::environment::authorization::AuthorizationTarget target;
        target.type = rebuntu::environment::authorization::TargetType::kFilesystem;
        
        auto result = policy.evaluate({
            Caller::current(),
            op,
            target,
            ScopeContext{}
        });
        
        CHECK(result.decision == AuthorizationDecision::kDeny);
    }
    
    // Test 6: AuthorizationContext current() constructs from process state
    {
        auto ctx = AuthorizationContext::current();
        
        std::cout << "Context caller UID: " << ctx.get_caller().uid 
                  << ", is_root: " << ctx.get_caller().is_root << "\\n";
        
        if (ctx.get_caller().is_root) {
            CHECK(ctx.get_scope().scope == rebuntu::environment::privilege::InstallationScope::kSystem);
        } else {
            CHECK(ctx.get_scope().scope == rebuntu::environment::privilege::InstallationScope::kUser);
        }
    }
    
    // Test 7: Non-root requires elevation for system writes
    {
        BasicAuthorizationPolicy policy;
        
        if (!Caller::current().is_root) {
            rebuntu::environment::authorization::RequestedOperation op;
            op.name = "system_install";
            op.op_class = rebuntu::environment::authorization::OperationClass::kWrite;
            
            rebuntu::environment::authorization::AuthorizationTarget target;
            target.type = rebuntu::environment::authorization::TargetType::kSystem;
            
            auto result = policy.evaluate({
                Caller::current(),
                op,
                target,
                ScopeContext{}
            });
            
            CHECK(result.decision == AuthorizationDecision::kRequireElevation);
        }
    }
    
    std::cout << "Authorization tests completed.\\n";
    
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\\n";
        return 1;
    }
    
    std::cout << "All authorization tests passed.\\n";
    return 0;
}
