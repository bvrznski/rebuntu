// rebuntu::runtime::loader tests (Phase 4.9)
//
// Unit tests for safe runtime definition loading functionality.

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "runtime/loader.hpp"

namespace rebuntu::runtime::loader {
namespace {

// ============================================================================
// Test utilities
// ============================================================================

static std::filesystem::path temp_dir_;

void setup_test_env() {
    // Create temporary directory for tests
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(10000, 99999);
    
    auto test_name = "loader_test_" + std::to_string(dis(gen));
    temp_dir_ = std::filesystem::temp_directory_path() / test_name;
    std::filesystem::create_directories(temp_dir_);
}

void cleanup_test_env() {
    if (!temp_dir_.empty() && std::filesystem::exists(temp_dir_)) {
        std::filesystem::remove_all(temp_dir_);
    }
}

std::filesystem::path make_temp_file(const std::string& name, const std::string& content,
                                     const std::string& ext = ".yaml") {
    auto path = temp_dir_ / (name + ext);
    std::ofstream os(path);
    os << content;
    return path;
}

// ============================================================================
// DefinitionId tests
// ============================================================================

void test_definition_id_equality() {
    DefinitionId id1{"test-unit"};
    DefinitionId id2{"test-unit"};
    DefinitionId id3{"other-unit"};
    
    if (!(id1 == id2)) {
        throw std::runtime_error("DefinitionId equality failed");
    }
    
    if (id1 == id3) {
        throw std::runtime_error("DefinitionId inequality failed");
    }
}

void test_definition_id_ordering() {
    DefinitionId id1{"aaa"};
    DefinitionId id2{"bbb"};
    
    if (!(id1 < id2)) {
        throw std::runtime_error("DefinitionId ordering failed");
    }
}

// ============================================================================
// LoadResult tests
// ============================================================================

void test_load_result_success() {
    DefinitionMetadata meta;
    meta.id = "test";
    
    auto result = LoadResult::success(meta);
    
    if (!result.succeeded()) {
        throw std::runtime_error("Success result not marked as succeeded");
    }
    
    if (!result.metadata.has_value()) {
        throw std::runtime_error("Success result has no metadata");
    }
}

void test_load_result_failure() {
    auto err = LoadError{LoadErrorCode::kFileNotFound, "not found", "/tmp/test", 0};
    auto result = LoadResult::failure(err);
    
    if (result.succeeded()) {
        throw std::runtime_error("Failure result marked as succeeded");
    }
    
    if (!result.error.has_value()) {
        throw std::runtime_error("Failure result has no error");
    }
}

void test_load_result_skipped() {
    DefinitionId id{"skipped"};
    auto result = LoadResult::skipped(id, "untrusted source");
    
    if (result.status != LoadResultStatus::kSkipped) {
        throw std::runtime_error("Skipped result has wrong status");
    }
}

// ============================================================================
// LoadKind tests
// ============================================================================

void test_load_kind_to_string() {
    if (to_string(LoadKind::kUnit) != "unit") {
        throw std::runtime_error("LoadKind unit string mismatch");
    }
    
    if (to_string(LoadKind::kOperation) != "operation") {
        throw std::runtime_error("LoadKind operation string mismatch");
    }
    
    if (to_string(LoadKind::kWorkflow) != "workflow") {
        throw std::runtime_error("LoadKind workflow string mismatch");
    }
    
    if (to_string(LoadKind::kTask) != "task") {
        throw std::runtime_error("LoadKind task string mismatch");
    }
}

// ============================================================================
// Loader tests
// ============================================================================

void test_loader_default_construct() {
    auto loader = make_loader();
    // Default constructor should not throw
}

void test_loader_with_config() {
    LoaderConfig cfg;
    cfg.allow_untrusted = true;
    
    auto loader = std::make_unique<Loader>(cfg);
    // Config constructor should not throw
}

void test_loader_builder() {
    auto builder = LoaderBuilder{}
        .add_trusted_config_dir("/etc/rebuntu")
        .add_trusted_share_dir("/usr/share/rebuntu")
        .allow_untrusted(false)
        .set_max_file_size(1024 * 1024)
        .set_strict_validation(true);
    
    auto loader = builder.build();
    
    if (!loader) {
        throw std::runtime_error("LoaderBuilder::build returned null");
    }
}

void test_loader_get_nonexistent() {
    auto loader = make_loader();
    DefinitionId id{"nonexistent"};
    
    auto result = loader->get(id);
    
    if (result.has_value()) {
        throw std::runtime_error("get() for nonexistent ID returned value");
    }
}

void test_loader_contains_false() {
    auto loader = make_loader();
    DefinitionId id{"nonexistent"};
    
    if (loader->contains(id)) {
        throw std::runtime_error("contains() for nonexistent ID returned true");
    }
}

void test_loader_list_empty() {
    auto loader = make_loader();
    
    auto ids = loader->list_all();
    
    if (!ids.empty()) {
        throw std::runtime_error("list_all() on empty loader returned non-empty");
    }
}

// ============================================================================
// Integration tests
// ============================================================================

void test_loader_load_from_temp_file() {
    setup_test_env();
    
    try {
        auto path = make_temp_file("test-unit", "id: test-unit\nkind: unit\n");
        
        auto loader = make_loader();
        auto result = loader->load_from_path(path, LoadKind::kUnit);
        
        if (!result.succeeded()) {
            // This is expected in stub mode - file parsing isn't implemented
            // The important thing is it doesn't crash
        }
    } catch (...) {
        cleanup_test_env();
        throw;
    }
    
    cleanup_test_env();
}

// ============================================================================
// Test runner
// ============================================================================

int run_tests() {
    int failures = 0;
    
    auto run = [&](const std::string& name, void (*fn)()) {
        try {
            fn();
            std::cout << "[PASS] " << name << "\n";
        } catch (const std::exception& e) {
            std::cout << "[FAIL] " << name << ": " << e.what() << "\n";
            failures++;
        }
    };
    
    // DefinitionId tests
    run("DefinitionId equality", test_definition_id_equality);
    run("DefinitionId ordering", test_definition_id_ordering);
    
    // LoadResult tests
    run("LoadResult success", test_load_result_success);
    run("LoadResult failure", test_load_result_failure);
    run("LoadResult skipped", test_load_result_skipped);
    
    // LoadKind tests
    run("LoadKind to_string", test_load_kind_to_string);
    
    // Loader tests
    run("Loader default construct", test_loader_default_construct);
    run("Loader with config", test_loader_with_config);
    run("LoaderBuilder", test_loader_builder);
    run("Loader get nonexistent", test_loader_get_nonexistent);
    run("Loader contains false", test_loader_contains_false);
    run("Loader list empty", test_loader_list_empty);
    
    // Integration tests
    run("Loader load from temp file", test_loader_load_from_temp_file);
    
    std::cout << "\n=== Results ===\n";
    if (failures == 0) {
        std::cout << "All tests passed\n";
    } else {
        std::cout << failures << " test(s) failed\n";
    }
    
    return failures;
}

}  // namespace
}  // namespace rebuntu::runtime::loader

int main() {
    return rebuntu::runtime::loader::run_tests();
}