// Unit tests for rebuntu::runtime::discovery (Phase 0.19)
#include <runtime/discovery.hpp>

#include <cstddef>
#include <iostream>
#include <string>

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
    using rebuntu::runtime::discovery::AliasResolver;
    using rebuntu::runtime::discovery::FilesystemScanner;
    using rebuntu::runtime::discovery::ProviderSelector;
    using rebuntu::runtime::discovery::ShellVerbDetector;
    using rebuntu::runtime::discovery::ShellVerbStatus;

    // ShellVerbDetector tests
    {
        ShellVerbDetector detector;
        
        // Initially all verbs are free
        CHECK(detector.is_verb_free("help") == true);
        CHECK(detector.is_verb_free("version") == true);
        
        // Add a reserved verb
        detector.add_reserved_verb("rebuntu_reserved");
        auto info = detector.detect("rebuntu_reserved");
        CHECK(info.status == ShellVerbStatus::REBUNTU);
    }

    // AliasResolver tests
    {
        AliasResolver resolver;
        
        // Test adding and resolving aliases
        resolver.add_alias({"filesystem.cp", "filesystem.copy", "Short alias for copy"});
        resolver.add_alias({"service.enable", "service.activate", ""});
        
        CHECK(resolver.contains("filesystem.cp") == true);
        CHECK(resolver.contains("nonexistent") == false);
        
        auto resolved = resolver.resolve("filesystem.cp");
        CHECK(resolved.has_value());
        CHECK(*resolved == "filesystem.copy");
    }

    // FilesystemScanner tests
    {
        std::vector<rebuntu::runtime::discovery::DiscoveryPath> paths;
        rebuntu::runtime::discovery::FilesystemScanner scanner(paths);
        
        // Basic scan - should return empty for non-existent path
        auto result = scanner.scan_all();
        CHECK(result.empty() == true);
    }

    // ProviderSelector tests
    {
        std::vector<OperationDefinition> ops;
        
        OperationDefinition op1;
        op1.id = "test.op";
        op1.title = "Test Operation";
        op1.description = "For testing";
        op1.subject_type = "filesystem.path";
        op1.provider_ids = {"provider_a", "provider_b"};
        
        ops.push_back(op1);
        
        ProviderSelector selector(ops);
        
        rebuntu::runtime::discovery::ProviderSelectionCriteria criteria;
        criteria.capability_id = "test.op";
        criteria.mode = rebuntu::runtime::discovery::ProviderSelectionMode::FIRST;
        
        auto result = selector.select(criteria);
        CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
        CHECK(result.value->size() == 2);
    }

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_discovery: OK\n";
    return 0;
}
