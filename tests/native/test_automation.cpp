// Unit tests for Rebuntu Automation contracts (Phase 0.12).
// Minimal, dependency-free assertion harness.

#include <automation/contracts.hpp>

#include <cstddef>
#include <iostream>
#include <string>
#include <chrono>

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
    using rebuntu::automation::TriggerKind;
    using rebuntu::automation::ActivationDecision;
    using rebuntu::automation::TargetKind;
    using rebuntu::automation::AutomatonState;
    using rebuntu::automation::ConcurrencyPolicy;
    using rebuntu::automation::ActivationPolicy;
    using rebuntu::automation::TargetReference;
    using rebuntu::automation::AutomationDefinition;
    using rebuntu::automation::ActivationRecord;
    using rebuntu::automation::AutomatonInstance;
    using rebuntu::automation::AutomationRegistry;
    using rebuntu::automation::ConditionEvaluator;
    using rebuntu::automation::PolicyEnforcer;

    std::cout << "Testing Phase 0.12 Automation contracts...\n";

    // Test: TriggerKind string conversions
    {
        CHECK(rebuntu::automation::to_string(TriggerKind::kEvent) == "event");
        CHECK(rebuntu::automation::to_string(TriggerKind::kSchedule) == "schedule");
        CHECK(rebuntu::automation::to_string(TriggerKind::kConditionTrue) == "condition_true");
        CHECK(rebuntu::automation::to_string(TriggerKind::kRequest) == "request");
    }

    // Test: ActivationDecision string conversions
    {
        CHECK(rebuntu::automation::to_string(ActivationDecision::kAllow) == "allow");
        CHECK(rebuntu::automation::to_string(ActivationDecision::kSuppress) == "suppress");
        CHECK(rebuntu::automation::to_string(ActivationDecision::kCoalesce) == "coalesce");
        CHECK(rebuntu::automation::to_string(ActivationDecision::kDefer) == "defer");
        CHECK(rebuntu::automation::to_string(ActivationDecision::kReject) == "reject");
    }

    // Test: TargetKind string conversions
    {
        CHECK(rebuntu::automation::to_string(TargetKind::kOperation) == "operation");
        CHECK(rebuntu::automation::to_string(TargetKind::kWorkflow) == "workflow");
    }

    // Test: AutomatonState string conversions
    {
        CHECK(rebuntu::automation::to_string(AutomatonState::kIdle) == "idle");
        CHECK(rebuntu::automation::to_string(AutomatonState::kEvaluating) == "evaluating");
        CHECK(rebuntu::automation::to_string(AutomatonState::kActivating) == "activating");
        CHECK(rebuntu::automation::to_string(AutomatonState::kRunning) == "running");
        CHECK(rebuntu::automation::to_string(AutomatonState::kWaiting) == "waiting");
    }

    // Test: ConcurrencyPolicy defaults
    {
        ConcurrencyPolicy policy;
        CHECK(policy.allow_concurrent == false);
        CHECK(policy.suppress_while_running == true);
        CHECK(!policy.cooldown_after_activation.has_value());
    }

    // Test: TargetReference construction
    {
        TargetReference ref;
        ref.kind = TargetKind::kOperation;
        ref.id = "filesystem.copy";

        CHECK(ref.kind == TargetKind::kOperation);
        CHECK(ref.id == "filesystem.copy");
    }

    // Test: AutomationDefinition construction
    {
        AutomationDefinition def;
        def.id = "test.automation";
        def.enabled = true;

        CHECK(def.id == "test.automation");
        CHECK(def.enabled == true);
        CHECK(def.trigger_kind == TriggerKind::kEvent);
        CHECK(def.kind == rebuntu::core::ComponentKind::kUnit);
    }

    // Test: ActivationRecord construction
    {
        ActivationRecord record;
        record.automation_id = "test.auto";
        record.trigger_kind = TriggerKind::kEvent;
        record.timestamp = std::chrono::system_clock::now();
        record.decision = ActivationDecision::kAllow;

        CHECK(record.automation_id == "test.auto");
        CHECK(record.trigger_kind == TriggerKind::kEvent);
        CHECK(record.decision == ActivationDecision::kAllow);
    }

    // Test: AutomatonInstance construction
    {
        AutomatonInstance inst;
        inst.definition_id = "auto-def-1";
        inst.state = AutomatonState::kIdle;

        CHECK(inst.definition_id == "auto-def-1");
        CHECK(inst.state == AutomatonState::kIdle);
        CHECK(inst.total_activations_attempted == 0);
    }

    // Test: AutomationRegistry - basic operations
    {
        AutomationRegistry registry;
        
        AutomationDefinition def1;
        def1.id = "auto1";
        registry.register_automation(def1);

        AutomationDefinition def2;
        def2.id = "auto2";
        def2.enabled = false;
        registry.register_automation(def2);

        CHECK(registry.contains("auto1") == true);
        CHECK(registry.contains("nonexistent") == false);

        auto found = registry.find("auto1");
        CHECK(found.has_value());
        CHECK(found->id == "auto1");

        auto enabled_list = registry.enabled();
        CHECK(enabled_list.size() == 1);
    }

    // Test: PolicyEnforcer - basic operations
    {
        PolicyEnforcer enforcer;
        
        CHECK(enforcer.check_activation("test-auto", false) == ActivationDecision::kAllow);

        enforcer.record_success("test-auto");
        enforcer.record_failure("test-auto");

        CHECK(enforcer.is_in_cooldown("test-auto") == true);
    }

    // Test: ConditionEvaluator - basic evaluation (prototype)
    {
        using rebuntu::runtime::Condition;
        using rebuntu::runtime::ConditionOperator;
        
        Condition cond;
        cond.lhs.path = "service.active";
        cond.op = ConditionOperator::kExists;

        ConditionEvaluator evaluator;
        bool result = evaluator.evaluate(cond);
        
        CHECK(result == true);
    }

    std::cout << "\nAutomation contract tests completed.\n";

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    
    std::cout << "test_automation: OK\n";
    return 0;
}
