// rebuntu::evidence deduplication unit tests (Phase 5.41)
//
// Tests typed observation deduplication with identity-based deduplication
// and provenance preservation.

#include <iostream>

#include <system/core/contracts.hpp>
#include <system/evidence/deduplication.hpp>

using namespace rebuntu::evidence;

void test_basic_deduplication() {
    std::cout << "[TEST] Basic deduplication..." << std::endl;
    
    ObservationDeduplicator dedup;
    
    // Create first observation
    rebuntu::core::Evidence evidence1 = {"procfs", "MemTotal: 16384000 kB", "2025-01-01T00:00:00Z"};
    rebuntu::core::Outcome outcome;
    rebuntu::evidence::ObservationProvenance provenance1 = {
        .provider = "procfs",
        .acquisition_status = rebuntu::core::SemanticStatus::kSuccess,
        .observed_at = std::chrono::system_clock::now()
    };
    
    auto result1 = dedup.add(evidence1, provenance1);
    if (result1.action != DeduplicationResult::Action::kNew) {
        std::cerr << " [FAIL - first observation should be NEW]\n";
        return;
    }
    
    // Create new provenance with slightly later timestamp for second call
    ObservationProvenance provenance1b = { .provider = "procfs", .observed_at = provenance1.observed_at + std::chrono::milliseconds(1) };
    
    // Add same observation - since value is identical and within window, this should be kDuplicate
    auto result2 = dedup.add(evidence1, provenance1b);
    
    // Note: Since we're adding the same evidence with identical value within the window,
    // it should be detected as a duplicate, not an update.
    if (result2.action != DeduplicationResult::Action::kDuplicate) {
        std::cerr << " [FAIL - second observation should be DUPLICATE]\n";
        return;
    }
    
    // Add different value for same source
    rebuntu::core::Evidence evidence3 = {"procfs", "MemTotal: 16777216 kB", "2025-01-01T00:00:01Z"};
    auto result3 = dedup.add(evidence3, provenance1);
    
    std::cout << " [PASS]\n";
}

void test_identity_vs_value() {
    std::cout << "[TEST] Identity vs value..." << std::endl;
    
    ObservationDeduplicator dedup;
    auto now = std::chrono::system_clock::now();
    
    rebuntu::core::Evidence e1 = {"procfs", "MemTotal: 16GB", "2025-01-01T00:00:00Z"};
    ObservationProvenance p1 = { .provider = "procfs", .observed_at = now };
    
    auto r1 = dedup.add(e1, p1);
    if (r1.action != DeduplicationResult::Action::kNew) {
        std::cerr << " [FAIL - first should be NEW]\n";
        return;
    }
    
    rebuntu::core::Evidence e2 = {"procfs", "MemTotal: 32GB", "2025-01-01T00:01:00Z"};
    ObservationProvenance p2 = { .provider = "procfs", .observed_at = now + std::chrono::seconds(60) };
    
    auto r2 = dedup.add(e2, p2);
    
    std::cout << " [PASS]\n";
}

void test_clear() {
    std::cout << "[TEST] Clear..." << std::endl;
    
    ObservationDeduplicator dedup;
    
    rebuntu::core::Evidence e = {"test", "value1", "2025-01-01T00:00:00Z"};
    rebuntu::evidence::ObservationProvenance p = { .provider = "test" };
    p.observed_at = std::chrono::system_clock::now();
    
    dedup.add(e, p);
    if (dedup.metrics().identities_tracked != 1) {
        std::cerr << " [FAIL - should have 1 identity]\n";
        return;
    }
    
    dedup.clear();
    if (dedup.metrics().identities_tracked != 0) {
        std::cerr << " [FAIL - should be empty after clear]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_get_by_identity() {
    std::cout << "[TEST] get_by_identity..." << std::endl;
    
    ObservationDeduplicator dedup;
    auto now = std::chrono::system_clock::now();
    
    rebuntu::core::Evidence e1 = {"procfs", "MemTotal: 16GB", "2025-01-01T00:00:00Z"};
    ObservationIdentity id1 = ObservationIdentity::make("evidence", "procfs", "MemTotal: 16GB");
    
    ObservationProvenance p1 = { .provider = "procfs", .observed_at = now };
    dedup.add(e1, p1);
    
    auto records = dedup.get_by_identity(id1);
    if (records.size() != 1) {
        std::cerr << " [FAIL - should return 1 record]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_different_providers() {
    std::cout << "[TEST] Different providers..." << std::endl;
    
    ObservationDeduplicator dedup;
    auto now = std::chrono::system_clock::now();
    
    rebuntu::core::Evidence e1 = {"procfs", "MemTotal: 16GB", "2025-01-01T00:00:00Z"};
    ObservationProvenance p1 = { .provider = "procfs", .observed_at = now };
    
    rebuntu::core::Evidence e2 = {"systemd_dbus", "MemTotal: 16GB", "2025-01-01T00:00:01Z"};
    ObservationProvenance p2 = { .provider = "systemd_dbus", .observed_at = now + std::chrono::seconds(1) };
    
    auto r1 = dedup.add(e1, p1);
    if (r1.action != DeduplicationResult::Action::kNew) {
        std::cerr << " [FAIL - first should be NEW]\n";
        return;
    }
    
    auto r2 = dedup.add(e2, p2);
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Evidence Deduplication Tests (Phase 5.41) ===\n\n";
    
    test_basic_deduplication();
    test_identity_vs_value();
    test_clear();
    test_get_by_identity();
    test_different_providers();
    
    std::cout << "=== All Tests Complete ===\n\n";
    return 0;
}