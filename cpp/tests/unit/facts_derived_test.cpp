// rebuntu - Phase 5.42 Derived Fact Boundary Unit Tests
//
// Unit tests for deterministic derivation of facts from observed data
// with explicit provenance tracking and epistemic classification.

#include "src/knowledge/facts/types.hpp"
#include "src/knowledge/facts/integration.hpp"
#include <iostream>
#include <cassert>

using namespace rebuntu::knowledge::facts;

void test_epistemic_class_to_string() {
    std::cout << "[TEST] EpistemicClass to_string...";
    
    assert(to_string(EpistemicClass::OBSERVATION) == "observation");
    assert(to_string(EpistemicClass::DETERMINISTIC_DERIVATION) == "deterministic_derivation");
    assert(to_string(EpistemicClass::CONFIGURED) == "configured");
    assert(to_string(EpistemicClass::UNKNOWN) == "unknown");
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_source_make_observation() {
    std::cout << "[TEST] DerivedFactSource make_observation...";
    
    auto source = DerivedFactSource::make_observation("/sys/class/net/eth0/address");
    
    assert(source.stable_id == "/sys/class/net/eth0/address");
    assert(!source.attribute.has_value());
    assert(!source.derivation_rule.has_value());
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_source_make_attribute() {
    std::cout << "[TEST] DerivedFactSource make_attribute...";
    
    auto source = DerivedFactSource::make_attribute("/sys/class/net/eth0", "speed");
    
    assert(source.stable_id == "/sys/class/net/eth0");
    assert(source.attribute.has_value());
    assert(source.attribute.value() == "speed");
    assert(!source.derivation_rule.has_value());
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_source_make_derivation() {
    std::cout << "[TEST] DerivedFactSource make_derivation...";
    
    auto source = DerivedFactSource::make_derivation("/sys/class/net/eth0", "speed_derivation_rule");
    
    assert(source.stable_id == "/sys/class/net/eth0");
    assert(!source.attribute.has_value());
    assert(source.derivation_rule.has_value());
    assert(source.derivation_rule.value() == "speed_derivation_rule");
    
    std::cout << " [PASS]\n";
}

void test_fact_default_constructs_with_observation_class() {
    std::cout << "[TEST] Fact default construct with OBSERVATION class...";
    
    Fact f;
    
    assert(f.epistemic_class == EpistemicClass::OBSERVATION);
    assert(f.key.empty());
    assert(f.value.empty());
    assert(f.sources.empty());
    assert(!f.derivation_rule.has_value());
    
    std::cout << " [PASS]\n";
}

void test_fact_with_derived_class() {
    std::cout << "[TEST] Fact with DETERMINISTIC_DERIVATION class...";
    
    Fact f;
    f.key = "system.memory.used_bytes";
    f.value = "4294967296";
    f.epistemic_class = EpistemicClass::DETERMINISTIC_DERIVATION;
    f.derivation_rule = "total - free - cached";
    
    assert(f.epistemic_class == EpistemicClass::DETERMINISTIC_DERIVATION);
    assert(f.key == "system.memory.used_bytes");
    assert(f.value == "4294967296");
    assert(f.derivation_rule.has_value());
    assert(f.derivation_rule.value() == "total - free - cached");
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_builder_build() {
    std::cout << "[TEST] DerivedFactBuilder build...";
    
    Fact f = DerivedFactBuilder()
        .set_key("system.memory.used_bytes")
        .set_value("4294967296")
        .set_derivation_rule("total - free - cached")
        .build();
    
    assert(f.key == "system.memory.used_bytes");
    assert(f.value == "4294967296");
    assert(f.epistemic_class == EpistemicClass::DETERMINISTIC_DERIVATION);
    assert(f.derivation_rule.has_value());
    assert(f.derivation_rule.value() == "total - free - cached");
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_builder_with_sources() {
    std::cout << "[TEST] DerivedFactBuilder with sources...";
    
    auto source1 = DerivedFactSource::make_observation("/proc/meminfo:MemTotal");
    auto source2 = DerivedFactSource::make_observation("/proc/meminfo:MemFree");
    
    Fact f = DerivedFactBuilder()
        .set_key("system.memory.used_bytes")
        .set_value("4294967296")
        .set_derivation_rule("total - free")
        .add_source(source1)
        .add_source(source2)
        .build();
    
    assert(f.sources.size() == 2);
    assert(f.sources[0].stable_id == "/proc/meminfo:MemTotal");
    assert(f.sources[1].stable_id == "/proc/meminfo:MemFree");
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_builder_build_with_class() {
    std::cout << "[TEST] DerivedFactBuilder build_with_class...";
    
    Fact f = DerivedFactBuilder()
        .set_key("system.config.value")
        .set_value("12345")
        .build_with_class(EpistemicClass::CONFIGURED);
    
    assert(f.epistemic_class == EpistemicClass::CONFIGURED);
    assert(f.key == "system.config.value");
    assert(f.value == "12345");
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_validator_valid() {
    std::cout << "[TEST] DerivedFactValidator validate valid fact...";
    
    Fact f;
    f.key = "test.key";
    f.value = "test.value";
    f.epistemic_class = EpistemicClass::OBSERVATION;
    
    DerivedFactValidator validator;
    assert(validator.validate(f) == true);
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_validator_with_sources_required() {
    std::cout << "[TEST] DerivedFactValidator requires sources for derivation...";
    
    Fact f;
    f.key = "test.key";
    f.value = "test.value";
    f.epistemic_class = EpistemicClass::DETERMINISTIC_DERIVATION;
    // No sources - should fail validation
    
    DerivedFactValidator validator;
    assert(validator.validate(f) == false);
    
    std::cout << " [PASS]\n";
}

void test_provenance_chain_add_observation() {
    std::cout << "[TEST] ProvenanceChain add_observation...";
    
    ProvenanceChain chain;
    auto now = std::chrono::system_clock::now();
    
    chain.add_observation("/proc/meminfo:MemTotal", now, true);
    
    assert(chain.size() == 1);
    assert(!chain.empty());
    
    const auto& records = chain.records();
    assert(records[0].stable_id == "/proc/meminfo:MemTotal");
    assert(records[0].verified == true);
    
    std::cout << " [PASS]\n";
}

void test_derived_fact_manager_register_rule() {
    std::cout << "[TEST] DerivedFactManager register_derivation_rule...";
    
    DerivedFactManager manager;
    manager.register_derivation_rule("memory_used", "total - free");
    
    assert(manager.has_derivation_rule("memory_used"));
    assert(!manager.has_derivation_rule("nonexistent"));
    
    auto desc = manager.get_derivation_rule_description("memory_used");
    assert(desc.has_value());
    assert(desc.value() == "total - free");
    
    std::cout << " [PASS]\n";
}

void test_empty_test() {
    // Placeholder to ensure at least one test runs
    std::cout << "[TEST] Empty placeholder...\n";
}

int main() {
    std::cout << "\n=== Derived Fact Boundary Tests ===\n\n";
    
    test_epistemic_class_to_string();
    test_derived_fact_source_make_observation();
    test_derived_fact_source_make_attribute();
    test_derived_fact_source_make_derivation();
    test_fact_default_constructs_with_observation_class();
    test_fact_with_derived_class();
    test_derived_fact_builder_build();
    test_derived_fact_builder_with_sources();
    test_derived_fact_builder_build_with_class();
    test_derived_fact_validator_valid();
    test_derived_fact_validator_with_sources_required();
    test_provenance_chain_add_observation();
    test_derived_fact_manager_register_rule();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}