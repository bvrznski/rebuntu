// Unit tests for rebuntu::runtime::initialization (Phase 4.1)
// Minimal, dependency-free assertion harness.
#include <runtime/initialization.hpp>

#include <iostream>
#include <chrono>
#include <map>

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
    using rebuntu::runtime::initialization::InitializationStage;
    using rebuntu::runtime::initialization::to_string;
    
    // Test initialization stage string conversions
    CHECK(to_string(InitializationStage::kNotStarted) == "not_started");
    CHECK(to_string(InitializationStage::kConfigResolve) == "config_resolve");
    CHECK(to_string(InitializationStage::kIdentityDiscover) == "identity_discover");
    CHECK(to_string(InitializationStage::kDependencyCheck) == "dependency_check");
    CHECK(to_string(InitializationStage::kProviderReady) == "provider_ready");
    CHECK(to_string(InitializationStage::kRuntimeReady) == "runtime_ready");
    
    // Test InitializationResult
    {
        rebuntu::runtime::initialization::InitializationResult result;
        CHECK(result.success == false);
        CHECK(result.final_stage == InitializationStage::kNotStarted);
        CHECK(result.is_complete() == false);
        
        result.success = true;
        result.final_stage = InitializationStage::kRuntimeReady;
        CHECK(result.success == true);
        CHECK(result.is_complete() == true);
    }
    
    // Test ConfigurationSource
    {
        rebuntu::runtime::initialization::ConfigurationSource source;
        source.name = "test";
        source.values["key1"] = "value1";
        source.optional = true;
        
        CHECK(source.name == "test");
        CHECK(source.values.find("key1") != source.values.end());
        CHECK(source.optional == true);
    }
    
    // Test HostIdentity
    {
        rebuntu::runtime::initialization::HostIdentity identity;
        CHECK(identity.is_valid() == false);  // no hostname or user_id
        
        identity.hostname = "testhost";
        identity.user_id = 1000;
        CHECK(identity.is_valid() == true);
        
        identity.group_id = 1000;
        identity.session_id = "session-001";
        identity.platform = "linux";
        
        CHECK(identity.hostname.has_value());
        CHECK(identity.user_id.has_value());
    }
    
    // Test InitializationPhase
    {
        rebuntu::runtime::initialization::InitializationPhase phase;
        phase.name = "test_phase";
        phase.stage = InitializationStage::kConfigResolve;
        phase.status = rebuntu::core::SemanticStatus::kSuccess;
        
        CHECK(phase.name == "test_phase");
        CHECK(phase.stage == InitializationStage::kConfigResolve);
        CHECK(phase.status == rebuntu::core::SemanticStatus::kSuccess);
    }
    
    // Test InitializationRegistry
    {
        rebuntu::runtime::initialization::InitializationRegistry registry;
        
        auto before_count = registry.all_phases().size();
        
        rebuntu::runtime::initialization::InitializationPhase phase;
        phase.name = "config";
        phase.stage = InitializationStage::kConfigResolve;
        phase.status = rebuntu::core::SemanticStatus::kSuccess;
        registry.add_phase(phase);
        
        auto after_count = registry.all_phases().size();
        
        // Registry should now have at least this phase recorded
        CHECK(after_count >= before_count);
        
        const auto* found = registry.get_phase(InitializationStage::kConfigResolve);
        CHECK(found != nullptr);
        if (found) {
            CHECK(found->name == "config");
        }
    }
    
    // Test InitializationContext
    {
        rebuntu::runtime::initialization::InitializationContext ctx;
        
        CHECK(ctx.timeout_ms.count() == 30000);  // default timeout
        CHECK(ctx.dry_run == false);
        
        ctx.timeout_ms = std::chrono::milliseconds(10000);
        ctx.dry_run = true;
        
        CHECK(ctx.timeout_ms.count() == 10000);
        CHECK(ctx.dry_run == true);
    }
    
    // Test Result type
    {
        using rebuntu::core::Result;
        
        Result<std::map<std::string, std::string>> result;
        result.status = rebuntu::core::SemanticStatus::kSuccess;
        
        std::map<std::string, std::string> values;
        values["key"] = "value";
        result.value = std::move(values);
        
        CHECK(result.has_value() == true);
        if (result.value) {
            CHECK(result.value->find("key") != result.value->end());
        }
    }
    
    // Test that Initializer can be instantiated
    {
        rebuntu::runtime::initialization::InitializationContext ctx;
        rebuntu::runtime::initialization::Initializer init(ctx);
        
        auto result = init.initialize();
        
        CHECK(result.success == true);
        CHECK(result.is_complete() == true);
        
        const auto& registry = init.registry();
        CHECK(registry.is_complete() == true);
    }
    
    // Test helper functions
    {
        std::vector<rebuntu::runtime::initialization::ConfigurationSource> sources;
        rebuntu::runtime::initialization::ConfigurationSource source;
        source.name = "defaults";
        source.values["config_key"] = "default_value";
        sources.push_back(source);
        
        auto config_result = rebuntu::runtime::initialization::resolve_configuration(sources);
        CHECK(config_result.status == rebuntu::core::SemanticStatus::kSuccess);
        
        if (config_result.has_value()) {
            auto it = config_result.value->find("config_key");
            CHECK(it != config_result.value->end());
            if (it != config_result.value->end()) {
                CHECK(it->second == "default_value");
            }
        }
    }
    
    // Test discover_host_identity
    {
        auto identity_result = rebuntu::runtime::initialization::discover_host_identity();
        CHECK(identity_result.status == rebuntu::core::SemanticStatus::kSuccess ||
              identity_result.status == rebuntu::core::SemanticStatus::kCompleted);
        
        if (identity_result.has_value()) {
            const auto& identity = *identity_result.value;
            // Should have at least some fields populated
            CHECK(identity.platform.has_value());
        }
    }
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_initialization: OK\n";
    return 0;
}