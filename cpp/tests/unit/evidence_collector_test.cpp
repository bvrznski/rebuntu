// rebuntu - Phase 5.12 Evidence Collector Unit Tests
//
// Unit tests for the evidence collector module.

#include <system/evidence/collector.hpp>
#include <iostream>

using namespace rebuntu::evidence;

void test_factory_creates_instance() {
    std::cout << "[TEST] Factory creates instance...";
    
    auto collector = make_evidence_collector();
    if (collector == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_configure_returns_success() {
    std::cout << "[TEST] Configure returns success...";
    
    auto collector = make_evidence_collector();
    EvidenceCollectorOptions options;
    core::Outcome outcome = collector->configure(options);
    
    if (outcome.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - configure did not succeed]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_start_stop_work() {
    std::cout << "[TEST] Start/stop works...";
    
    auto collector = make_evidence_collector();
    
    core::Outcome start_outcome = collector->start();
    if (start_outcome.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - start did not succeed]\n";
        return;
    }
    
    if (!collector->is_running()) {
        std::cerr << " [FAIL - should be running after start]\n";
        return;
    }
    
    core::Outcome stop_outcome = collector->stop();
    if (stop_outcome.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - stop did not succeed]\n";
        return;
    }
    
    if (collector->is_running()) {
        std::cerr << " [FAIL - should not be running after stop]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_evidence_request_make() {
    std::cout << "[TEST] EvidenceRequest::make creates valid request...";
    
    auto request = EvidenceRequest::make("test-123");
    
    if (request.id != "test-123") {
        std::cerr << " [FAIL - wrong id]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_evidence_budget_make_default() {
    std::cout << "[TEST] EvidenceBudget::make_default sets values...";
    
    auto budget = EvidenceBudget::make_default();
    
    if (budget.max_total_records == 0) {
        std::cerr << " [FAIL - max_total_records is 0]\n";
        return;
    }
    
    if (budget.collector_budgets.size() == 0) {
        std::cerr << " [FAIL - no collector budgets]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_collector_registry_register_and_find() {
    std::cout << "[TEST] CollectorRegistry register and find...";
    
    CollectorRegistry registry;
    
    CollectorInfo info;
    info.kind = EvidenceKind::kJournalSlice;
    info.name = "journal";
    info.enabled_by_default = true;
    
    registry.register_collector(info);
    
    if (!registry.contains(EvidenceKind::kJournalSlice)) {
        std::cerr << " [FAIL - contains returned false]\n";
        return;
    }
    
    auto found = registry.find(EvidenceKind::kJournalSlice);
    if (!found.has_value()) {
        std::cerr << " [FAIL - find returned nullopt]\n";
        return;
    }
    
    if (found->name != "journal") {
        std::cerr << " [FAIL - wrong name]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_evidence_collection_result_success() {
    std::cout << "[TEST] EvidenceCollectionResult::success creates valid result...";
    
    auto result = EvidenceCollectionResult::success();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - wrong status]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Evidence Collector Tests ===\n\n";
    
    test_factory_creates_instance();
    test_configure_returns_success();
    test_start_stop_work();
    test_evidence_request_make();
    test_evidence_budget_make_default();
    test_collector_registry_register_and_find();
    test_evidence_collection_result_success();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}