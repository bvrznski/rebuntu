// rebuntu - Phase 6.2 Predicate Dictionary Unit Tests
//
// Unit tests for predicate functions.

#include "rebuntu/shell/types.hpp"
#include "rebuntu/shell/predicates.hpp"

#include <iostream>

using namespace rebuntu::shell;

void test_predicate_result_make_true() {
    std::cout << "[TEST] PredicateResult::make_true creates valid result...";
    
    auto result = PredicateResult::true_result();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - wrong status]\n";
        return;
    }
    
    if (!result.is_true.has_value() || !result.is_true.value()) {
        std::cerr << " [FAIL - is_true should be true]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_predicate_result_make_false() {
    std::cout << "[TEST] PredicateResult::make_false creates valid result...";
    
    auto result = PredicateResult::false_result();
    
    if (result.status != core::SemanticStatus::kFailure) {
        std::cerr << " [FAIL - wrong status]\n";
        return;
    }
    
    if (!result.is_true.has_value() || result.is_true.value()) {
        std::cerr << " [FAIL - is_true should be false]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_predicate_result_make_unknown() {
    std::cout << "[TEST] PredicateResult::unknown creates valid result...";
    
    auto result = PredicateResult::unknown("test error message");
    
    if (result.status != core::SemanticStatus::kUnknown) {
        std::cerr << " [FAIL - wrong status]\n";
        return;
    }
    
    if (!result.is_true.has_value()) {
        std::cerr << " [FAIL - is_true should be nullopt for unknown]\n";
        return;
    }
    
    if (!result.error.has_value() || result.error->code != "E_UNKNOWN") {
        std::cerr << " [FAIL - error not set correctly]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_predicate_result_evidence_preservation() {
    std::cout << "[TEST] PredicateResult preserves evidence...";
    
    core::Evidence e;
    e.source = "test-source";
    e.value = "test-value";
    e.captured_at = "2026-01-01T00:00:00Z";
    
    auto result = PredicateResult::true_result();
    result.evidence.push_back(e);
    
    if (result.evidence.size() != 1) {
        std::cerr << " [FAIL - evidence not preserved]\n";
        return;
    }
    
    if (result.evidence[0].source != "test-source") {
        std::cerr << " [FAIL - wrong source in evidence]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_predicate_kind_to_string() {
    std::cout << "[TEST] PredicateKind to_string conversion...";
    
    if (to_string(PredicateKind::kPackage) != "package") {
        std::cerr << " [FAIL - kPackage string mismatch]\n";
        return;
    }
    
    if (to_string(PredicateKind::kService) != "service") {
        std::cerr << " [FAIL - kService string mismatch]\n";
        return;
    }
    
    if (to_string(PredicateKind::kProcess) != "process") {
        std::cerr << " [FAIL - kProcess string mismatch]\n";
        return;
    }
    
    if (to_string(PredicateKind::kFilesystem) != "filesystem") {
        std::cerr << " [FAIL - kFilesystem string mismatch]\n";
        return;
    }
    
    if (to_string(PredicateKind::kNetwork) != "network") {
        std::cerr << " [FAIL - kNetwork string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_predicate_result_unknown_value() {
    std::cout << "[TEST] PredicateResult with unknown value (is_true == nullopt)...";
    
    auto result = PredicateResult::unknown("cannot determine state");
    
    // UNKNOWN means is_true has no value (nullopt)
    if (result.is_true.has_value()) {
        std::cerr << " [FAIL - is_true should be nullopt for unknown]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Predicate Dictionary Tests ===\n\n";
    
    test_predicate_result_make_true();
    test_predicate_result_make_false();
    test_predicate_result_make_unknown();
    test_predicate_result_evidence_preservation();
    test_predicate_kind_to_string();
    test_predicate_result_unknown_value();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}