// Unit tests for rebuntu::core Operation contracts (Phase 0.10).
// Minimal, dependency-free assertion harness.

#include <system/core/contracts.hpp>

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {
int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)
}  // namespace

int main() {
    using rebuntu::core::OperationDefinition;
    using rebuntu::core::OperationRegistry;
    using rebuntu::core::OperationResult;
    using rebuntu::core::PreconditionResult;
    using rebuntu::core::SideEffectKind;
    using rebuntu::core::Idempotency;
    using rebuntu::core::Reversibility;
    using rebuntu::core::SemanticStatus;
    using rebuntu::core::to_string;

    std::cout << "Testing Phase 0.10 Operation contracts...\n";

    // Test: OperationRegistry registers operations
    {
        OperationRegistry registry;
        
        OperationDefinition op_def;
        op_def.id = "filesystem.copy";
        op_def.title = "Copy a file";
        op_def.description = "Copies a source file to a destination path";
        op_def.subject_type = "filesystem.path";
        op_def.side_effect = SideEffectKind::MUTATING;
        op_def.idempotency = Idempotency::CONDITIONALLY_IDEMPOTENT;
        
        registry.register_operation(op_def);
        
        CHECK(registry.contains("filesystem.copy"));
        
        auto found = registry.find("filesystem.copy");
        CHECK(found.has_value());
        CHECK(found->id == "filesystem.copy");
    }

    // Test: OperationRegistry finds by subject type
    {
        OperationRegistry registry;
        
        {
            OperationDefinition op;
            op.id = "filesystem.copy";
            op.subject_type = "filesystem.path";
            op.side_effect = SideEffectKind::MUTATING;
            registry.register_operation(op);
        }
        {
            OperationDefinition op;
            op.id = "filesystem.exists";
            op.subject_type = "filesystem.path";
            op.side_effect = SideEffectKind::OBSERVATION;
            registry.register_operation(op);
        }
        
        auto fs_ops = registry.by_subject("filesystem.path");
        CHECK(fs_ops.size() == 2);
    }

    // Test: OperationResult success
    {
        auto result = OperationResult::success(true, true);
        
        CHECK(result.status == SemanticStatus::kSuccess);
        CHECK(result.verified == true);
        CHECK(result.is_success() == true);
    }

    // Test: OperationResult no_change (no-op)
    {
        auto result = OperationResult::no_change();
        
        CHECK(result.status == SemanticStatus::kSuccess);
        CHECK(result.changed == false);
        CHECK(result.verified == true);
    }

    // Test: OperationResult failure
    {
        auto result = OperationResult::failure("E_NOT_FOUND", "File does not exist");
        
        CHECK(result.status == SemanticStatus::kFailure);
        CHECK(result.error.has_value());
        CHECK(result.error->code == "E_NOT_FOUND");
    }

    // Test: SideEffectKind string conversions
    {
        CHECK(to_string(SideEffectKind::NONE) == "none");
        CHECK(to_string(SideEffectKind::OBSERVATION) == "observation");
        CHECK(to_string(SideEffectKind::MUTATING) == "mutating");
        CHECK(to_string(SideEffectKind::PRIVILEGED) == "privileged");
        CHECK(to_string(SideEffectKind::DESTRUCTIVE) == "destructive");
    }

    // Test: Idempotency string conversions
    {
        CHECK(to_string(Idempotency::IDEMPOTENT) == "idempotent");
        CHECK(to_string(Idempotency::CONDITIONALLY_IDEMPOTENT) == "conditionally_idempotent");
        CHECK(to_string(Idempotency::NON_IDEMPOTENT) == "non_idempotent");
        CHECK(to_string(Idempotency::UNKNOWN) == "unknown");
    }

    // Test: Reversibility string conversions
    {
        CHECK(to_string(Reversibility::REVERSIBLE) == "reversible");
        CHECK(to_string(Reversibility::CONDITIONALLY_REVERSIBLE) == "conditionally_reversible");
        CHECK(to_string(Reversibility::IRREVERSIBLE) == "irreversible");
        CHECK(to_string(Reversibility::UNKNOWN) == "unknown");
    }

    // Test: PreconditionResult string conversions
    {
        CHECK(to_string(PreconditionResult::SATISFIED) == "satisfied");
        CHECK(to_string(PreconditionResult::FAILED) == "failed");
        CHECK(to_string(PreconditionResult::WARNING) == "warning");
    }

    // Test: OperationRegistry validation
    {
        OperationRegistry registry;
        
        // Register valid operations
        {
            OperationDefinition op;
            op.id = "filesystem.copy";
            op.title = "Copy file";
            op.description = "Copies a file";
            op.subject_type = "filesystem.path";
            registry.register_operation(op);
        }
        
        auto issues = registry.validate();
        CHECK(issues.empty());
    }

    // Test: OperationRegistry detects missing title
    {
        OperationRegistry registry;
        
        {
            OperationDefinition op;
            op.id = "filesystem.missing_title";
            op.description = "Has no title";  // empty title
            op.subject_type = "filesystem.path";
            registry.register_operation(op);
        }
        
        auto issues = registry.validate();
        bool found_issue = false;
        for (const auto& issue : issues) {
            if (issue.find("missing title") != std::string::npos) {
                found_issue = true;
                break;
            }
        }
        CHECK(found_issue);
    }

    std::cout << "\nOperation contract tests completed.\n";
    
    return g_failures > 0 ? 1 : 0;
}
