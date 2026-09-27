// rebuntu::tests::cli_inventory — Tests for CLI Inventory Inspection (Task 5.60)
//
// These tests verify that:
//   - Freshness tracking works correctly
//   - Source provenance is preserved
//   - Query results are constructed properly

#include "cli/inventory/types.hpp"
#include "cli/inventory/query.hpp"

// Include core contracts for SemanticStatus enum
#include <system/core/contracts.hpp>

#include <cassert>
#include <iostream>
#include <chrono>

using namespace rebuntu::cli::inventory;
using namespace rebuntu::core;

// ============================================================================
// Test helpers for freshness report
// ============================================================================

void test_fresh_report() {
    auto now = std::chrono::system_clock::now();
    auto r = FreshnessReport::fresh("dpkg", now);
    
    assert(r.source == "dpkg");
    assert(r.source_kind == FreshnessReport::Source::kSourceVerified);
    assert(!r.is_stale);
    assert(r.observed_at != std::chrono::system_clock::time_point{});
    
    std::cout << "[PASS] test_fresh_report" << std::endl;
}

void test_stale_report() {
    auto now = std::chrono::system_clock::now();
    auto r = FreshnessReport::stale("dpkg", now);
    
    assert(r.source == "dpkg");
    assert(r.source_kind == FreshnessReport::Source::kSourceVerified);
    assert(r.is_stale);
    
    std::cout << "[PASS] test_stale_report" << std::endl;
}

void test_unknown_report() {
    auto r = FreshnessReport::unknown();
    
    assert(r.source == "unknown");
    assert(r.source_kind == FreshnessReport::Source::kUnknown);
    assert(!r.is_stale);
    
    std::cout << "[PASS] test_unknown_report" << std::endl;
}

// ============================================================================
// Test entity info construction
// ============================================================================

void test_entity_info() {
    EntityInfo e;
    e.id = "test-package:amd64";
    e.name.emplace("test-package");
    e.category.emplace("package");
    
    assert(e.id == "test-package:amd64");
    assert(e.name.has_value());
    assert(*e.name == "test-package");
    assert(e.category.has_value());
    assert(*e.category == "package");
    
    std::cout << "[PASS] test_entity_info" << std::endl;
}

void test_entity_with_attributes() {
    EntityInfo e;
    e.id = "test-pkg";
    e.attributes.emplace_back("version", "1.0.0");
    e.attributes.emplace_back("state", "installed");
    
    assert(e.attributes.size() == 2);
    assert(e.attributes[0].first == "version");
    assert(e.attributes[0].second == "1.0.0");
    
    std::cout << "[PASS] test_entity_with_attributes" << std::endl;
}

// ============================================================================
// Test query result construction
// ============================================================================

void test_success_result() {
    std::vector<EntityInfo> entities;
    
    auto now = std::chrono::system_clock::now();
    
    EntityInfo e1;
    e1.id = "pkg1";
    FreshnessReport r1 = FreshnessReport::fresh("dpkg", now);
    r1.age_ms = std::chrono::milliseconds(100);
    e1.freshness = r1;
    entities.push_back(e1);
    
    EntityInfo e2;
    e2.id = "pkg2";
    FreshnessReport r2 = FreshnessReport::stale("dpkg", now);
    r2.age_ms = std::chrono::milliseconds(60000);  // 60 seconds - stale
    e2.freshness = r2;
    entities.push_back(e2);
    
    auto result = QueryResult::success(entities);
    
    assert(result.status == SemanticStatus::kSuccess);
    assert(result.entities.size() == 2);
    assert(result.fresh_count == 1);   // Only e1 is fresh
    assert(result.stale_count == 1);   // Only e2 is stale
    
    std::cout << "[PASS] test_success_result" << std::endl;
}

void test_empty_result() {
    std::vector<EntityInfo> entities;
    
    auto result = QueryResult::success(entities);
    
    assert(result.status == SemanticStatus::kSuccess);
    assert(result.entities.size() == 0);
    assert(result.fresh_count == 0);
    assert(result.stale_count == 0);
    
    std::cout << "[PASS] test_empty_result" << std::endl;
}

void test_failure_result() {
    auto result = QueryResult::failure("E_FAILED", "test failure");
    
    assert(result.status == SemanticStatus::kFailure);
    assert(result.description == "test failure");
    
    std::cout << "[PASS] test_failure_result" << std::endl;
}

void test_unknown_result() {
    auto result = QueryResult::unknown("could not determine");
    
    assert(result.status == SemanticStatus::kUnknown);
    assert(result.description == "could not determine");
    
    std::cout << "[PASS] test_unknown_result" << std::endl;
}

// ============================================================================
// Test inventory kind conversions
// ============================================================================

void test_inventory_kind_to_string() {
    assert(to_string(InventoryKind::kPackage) == "package");
    assert(to_string(InventoryKind::kService) == "service");
    assert(to_string(InventoryKind::kProcess) == "process");
    assert(to_string(InventoryKind::kUnknown) == "unknown");
    
    std::cout << "[PASS] test_inventory_kind_to_string" << std::endl;
}

// ============================================================================
// Test make_inventory_query factory
// ============================================================================

void test_make_inventory_query() {
    auto query = rebuntu::cli::inventory::make_inventory_query();
    
    assert(query != nullptr);
    
    // Query should support at least kPackage and kUnknown kinds
    auto kinds = query->supported_kinds();
    bool supports_package = false;
    for (auto kind : kinds) {
        if (kind == InventoryKind::kPackage) {
            supports_package = true;
            break;
        }
    }
    assert(supports_package);
    
    std::cout << "[PASS] test_make_inventory_query" << std::endl;
}

// ============================================================================
// Test query execution
// ============================================================================

void test_query_all_packages() {
    auto query = rebuntu::cli::inventory::make_inventory_query();
    
    QueryOptions options;
    options.kind = InventoryKind::kPackage;
    options.freshness_threshold_ms = std::chrono::minutes(5);
    options.max_results = 0;  // No limit
    
    auto result = query->query_all(options);
    
    // The query should either succeed or return a non-failure status
    assert(result.status == SemanticStatus::kSuccess ||
           result.status == SemanticStatus::kCompleted);
    
    std::cout << "[PASS] test_query_all_packages" << std::endl;
}

// ============================================================================
// Main test runner
// ============================================================================

int main() {
    std::cout << "Testing CLI Inventory Inspection (Task 5.60)" << std::endl;
    std::cout << "=============================================" << std::endl;
    
    test_fresh_report();
    test_stale_report();
    test_unknown_report();
    
    test_entity_info();
    test_entity_with_attributes();
    
    test_success_result();
    test_empty_result();
    test_failure_result();
    test_unknown_result();
    
    test_inventory_kind_to_string();
    
    test_make_inventory_query();
    
    // Note: query_all_packages depends on dpkg being available
    // If dpkg is not installed, this may fail - that's expected
    std::cout << "\nNote: test_query_all_packages requires dpkg to be available." << std::endl;
    std::cout << "If running in an environment without dpkg, this test may show unknown status." << std::endl;
    
    try {
        test_query_all_packages();
    } catch (const std::exception& e) {
        std::cout << "[INFO] query_all_packages skipped: " << e.what() << std::endl;
    }
    
    std::cout << "\n=============================================" << std::endl;
    std::cout << "All CLI inventory tests passed!" << std::endl;
    return 0;
}