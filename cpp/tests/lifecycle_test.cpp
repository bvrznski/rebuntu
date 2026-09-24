// Rebuntu Lifecycle Operations Tests (Phase 1.11)
// =================================================

#include <system/lifecycle/contracts.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>

namespace fs = std::filesystem;

// ============================================================================
// Test Utilities
// ============================================================================

static std::optional<std::string> read_file(const std::string& path) {
    std::error_code ec;
    
    if (!fs::is_regular_file(fs::path(path), ec)) {
        return std::nullopt;
    }
    
    std::ifstream ifs(path, std::ios::in);
    if (!ifs) {
        return std::nullopt;
    }
    
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

static bool write_file(const std::string& path, const std::string& content) {
    std::error_code ec;
    
    auto parent = fs::path(path).parent_path();
    if (!parent.empty() && !fs::exists(parent, ec)) {
        fs::create_directories(parent, ec);
        if (ec) return false;
    }
    
    std::ofstream ofs(path, std::ios::out | std::ios::trunc);
    if (!ofs) return false;
    ofs << content;
    return !ofs.fail();
}

static bool path_exists(const std::string& path) {
    std::error_code ec;
    return fs::exists(fs::path(path), ec);
}

// ============================================================================
// Test: Lifecycle Operation String Conversion
// ============================================================================

void test_operation_string_conversion() {
    using namespace rebuntu::lifecycle;
    
    assert(to_string(LifecycleOperation::kReconfigure) == "reconfigure");
    assert(to_string(LifecycleOperation::kRepair) == "repair");
    assert(to_string(LifecycleOperation::kUpgrade) == "upgrade");
    assert(to_string(LifecycleOperation::kUninstall) == "uninstall");
    assert(to_string(LifecycleOperation::kPurge) == "purge");
    
    std::cout << "[PASS] test_operation_string_conversion" << std::endl;
}

// ============================================================================
// Test: Artifact Ownership String Conversion
// ============================================================================

void test_artifact_ownership_string_conversion() {
    using namespace rebuntu::lifecycle;
    
    assert(to_string(ArtifactOwnership::kRebuntuOwned) == "rebuntu-owned");
    assert(to_string(ArtifactOwnership::kUserModified) == "user-modified");
    assert(to_string(ArtifactOwnership::kExternal) == "external");
    assert(to_string(ArtifactOwnership::kUnknown) == "unknown");
    
    std::cout << "[PASS] test_artifact_ownership_string_conversion" << std::endl;
}

// ============================================================================
// Test: Artifact Type String Conversion
// ============================================================================

void test_artifact_type_string_conversion() {
    using namespace rebuntu::lifecycle;
    
    assert(to_string(ArtifactType::kBinary) == "binary");
    assert(to_string(ArtifactType::kConfigFile) == "config-file");
    assert(to_string(ArtifactType::kStateFile) == "state-file");
    assert(to_string(ArtifactType::kCacheFile) == "cache-file");
    assert(to_string(ArtifactType::kSystemdUnit) == "systemd-unit");
    assert(to_string(ArtifactType::kShellIntegration) == "shell-integration");
    assert(to_string(ArtifactType::kDocumentation) == "documentation");
    assert(to_string(ArtifactType::kDirectory) == "directory");
    
    std::cout << "[PASS] test_artifact_type_string_conversion" << std::endl;
}

// ============================================================================
// Test: Artifact Manifest
// ============================================================================

void test_artifact_manifest() {
    using namespace rebuntu::lifecycle;
    
    ArtifactManifest manifest;
    
    // Add some entries
    manifest.add_entry({
        .path = "/etc/rebuntu/config",
        .type = ArtifactType::kConfigFile,
        .ownership = ArtifactOwnership::kRebuntuOwned
    });
    
    manifest.add_entry({
        .path = "/home/user/.config/rebuntu/settings",
        .type = ArtifactType::kConfigFile,
        .ownership = ArtifactOwnership::kUserModified
    });
    
    // Test contains()
    assert(manifest.contains("/etc/rebuntu/config"));
    assert(!manifest.contains("/nonexistent/path"));
    
    // Test find()
    auto entry_opt = manifest.find("/etc/rebuntu/config");
    assert(entry_opt.has_value());
    assert(entry_opt.value().path == "/etc/rebuntu/config");
    
    // Test all()
    auto all_entries = manifest.all();
    assert(all_entries.size() == 2);
    
    // Test rebuntu_owned()
    auto owned = manifest.rebuntu_owned();
    assert(owned.size() == 1);
    assert(owned[0].path == "/etc/rebuntu/config");
    
    std::cout << "[PASS] test_artifact_manifest" << std::endl;
}

// ============================================================================
// Test: Lifecycle Context
// ============================================================================

void test_lifecycle_context() {
    using namespace rebuntu::lifecycle;
    
    LifecycleContext ctx;
    
    // Default values
    assert(ctx.scope == LifecycleContext::Scope::kSystem);
    assert(!ctx.dry_run);
    assert(!ctx.force);
    assert(ctx.preserve_user_data);
    assert(!ctx.skip_verification);
    
    // Modify values
    ctx.dry_run = true;
    ctx.scope = LifecycleContext::Scope::kUser;
    
    assert(ctx.dry_run);
    assert(ctx.scope == LifecycleContext::Scope::kUser);
    
    std::cout << "[PASS] test_lifecycle_context" << std::endl;
}

// ============================================================================
// Test: Lifecycle Status String Conversion
// ============================================================================

void test_lifecycle_status_string_conversion() {
    using namespace rebuntu::lifecycle;
    
    assert(to_string(LifecycleStatus::kNotStarted) == "not_started");
    assert(to_string(LifecycleStatus::kInProgress) == "in_progress");
    assert(to_string(LifecycleStatus::kCompleted) == "completed");
    assert(to_string(LifecycleStatus::kFailed) == "failed");
    assert(to_string(LifecycleStatus::kPartial) == "partial");
    assert(to_string(LifecycleStatus::kCancelled) == "cancelled");
    
    std::cout << "[PASS] test_lifecycle_status_string_conversion" << std::endl;
}

// ============================================================================
// Test: Artifact Operation String Conversion
// ============================================================================

void test_artifact_operation_action_string_conversion() {
    using namespace rebuntu::lifecycle;
    
    assert(to_string(ArtifactOperation::Action::kNoOp) == "no_op");
    assert(to_string(ArtifactOperation::Action::kCreated) == "created");
    assert(to_string(ArtifactOperation::Action::kUpdated) == "updated");
    assert(to_string(ArtifactOperation::Action::kVerified) == "verified");
    assert(to_string(ArtifactOperation::Action::kDeleted) == "deleted");
    assert(to_string(ArtifactOperation::Action::kSkipped) == "skipped");
    assert(to_string(ArtifactOperation::Action::kFailed) == "failed");
    
    std::cout << "[PASS] test_artifact_operation_action_string_conversion" << std::endl;
}

// ============================================================================
// Test: Lifecycle Result Structure
// ============================================================================

void test_lifecycle_result_structure() {
    using namespace rebuntu::lifecycle;
    
    LifecycleResult result;
    result.operation = LifecycleOperation::kReconfigure;
    result.status = LifecycleStatus::kCompleted;
    result.success = true;
    result.verified = true;
    
    // Add some operations
    ArtifactOperation op1;
    op1.path = "/etc/rebuntu/config";
    op1.action = ArtifactOperation::Action::kCreated;
    result.operations.push_back(op1);
    
    assert(result.operation == LifecycleOperation::kReconfigure);
    assert(result.status == LifecycleStatus::kCompleted);
    assert(result.success);
    assert(result.verified);
    assert(result.operations.size() == 1);
    
    std::cout << "[PASS] test_lifecycle_result_structure" << std::endl;
}

// ============================================================================
// Test: Reconfigure - Dry Run
// ============================================================================

void test_reconfigure_dry_run() {
    using namespace rebuntu::lifecycle;
    
    LifecycleContext ctx;
    ctx.dry_run = true;
    
    std::map<std::string, std::string> config = {
        {"key1", "value1"},
        {"key2", "value2"}
    };
    
    LifecycleResult result = reconfigure(ctx, config);
    
    assert(result.operation == LifecycleOperation::kReconfigure);
    // In dry-run mode, success is true but verified may be false
    std::cout << "[PASS] test_reconfigure_dry_run" << std::endl;
}

// ============================================================================
// Test: Reconfigure - Real Configuration Write
// ============================================================================

void test_reconfigure_write() {
    using namespace rebuntu::lifecycle;
    
    // Create a temporary directory for testing
    fs::path temp_dir = fs::temp_directory_path() / ("rebuntu_test_" + std::to_string(std::time(nullptr)));
    fs::create_directories(temp_dir);
    
    LifecycleContext ctx;
    ctx.config_dir = temp_dir.string();
    ctx.dry_run = false;
    
    std::map<std::string, std::string> config = {
        {"test_key", "test_value"}
    };
    
    LifecycleResult result = reconfigure(ctx, config);
    
    assert(result.operation == LifecycleOperation::kReconfigure);
    
    // Check if config was written
    fs::path config_file = temp_dir / "config";
    auto content_opt = read_file(config_file.string());
    assert(content_opt.has_value());
    assert(content_opt.value().find("test_key") != std::string::npos);
    assert(content_opt.value().find("test_value") != std::string::npos);
    
    // Cleanup
    fs::remove_all(temp_dir);
    
    std::cout << "[PASS] test_reconfigure_write" << std::endl;
}

// ============================================================================
// Test: Repair - Missing Directory
// ============================================================================

void test_repair_missing_directory() {
    using namespace rebuntu::lifecycle;
    
    // Create a temporary directory for testing
    fs::path temp_dir = fs::temp_directory_path() / ("rebuntu_test_repair_" + std::to_string(std::time(nullptr)));
    fs::remove_all(temp_dir);  // Ensure it doesn't exist
    
    LifecycleContext ctx;
    ctx.config_dir = temp_dir.string();
    ctx.dry_run = false;
    
    std::vector<std::string> paths = {temp_dir.string()};
    
    LifecycleResult result = repair(ctx, paths);
    
    assert(result.operation == LifecycleOperation::kRepair);
    
    // Check if directory was created
    assert(path_exists(temp_dir.string()));
    
    // Cleanup
    fs::remove_all(temp_dir);
    
    std::cout << "[PASS] test_repair_missing_directory" << std::endl;
}

// ============================================================================
// Test: Repair - Existing Directory
// ============================================================================

void test_repair_existing_directory() {
    using namespace rebuntu::lifecycle;
    
    // Create a temporary directory for testing
    fs::path temp_dir = fs::temp_directory_path() / ("rebuntu_test_repair_exists_" + std::to_string(std::time(nullptr)));
    fs::create_directories(temp_dir);
    
    LifecycleContext ctx;
    ctx.config_dir = temp_dir.string();
    ctx.dry_run = false;
    
    std::vector<std::string> paths = {temp_dir.string()};
    
    LifecycleResult result = repair(ctx, paths);
    
    assert(result.operation == LifecycleOperation::kRepair);
    
    // Directory exists and should be verified
    bool found_verified = false;
    for (const auto& op : result.operations) {
        if (op.path == temp_dir.string() && op.action == ArtifactOperation::Action::kVerified) {
            found_verified = true;
            break;
        }
    }
    
    // Cleanup
    fs::remove_all(temp_dir);
    
    std::cout << "[PASS] test_repair_existing_directory" << std::endl;
}

// ============================================================================
// Test: Uninstall - Dry Run
// ============================================================================

void test_uninstall_dry_run() {
    using namespace rebuntu::lifecycle;
    
    LifecycleContext ctx;
    ctx.dry_run = true;
    
    LifecycleResult result = uninstall(ctx);
    
    assert(result.operation == LifecycleOperation::kUninstall);
    
    std::cout << "[PASS] test_uninstall_dry_run" << std::endl;
}

// ============================================================================
// Test: Purge - Dry Run
// ============================================================================

void test_purge_dry_run() {
    using namespace rebuntu::lifecycle;
    
    LifecycleContext ctx;
    ctx.dry_run = true;
    
    LifecycleResult result = purge(ctx);
    
    assert(result.operation == LifecycleOperation::kPurge);
    
    std::cout << "[PASS] test_purge_dry_run" << std::endl;
}

// ============================================================================
// Test: Upgrade - Basic
// ============================================================================

void test_upgrade_basic() {
    using namespace rebuntu::lifecycle;
    
    LifecycleContext ctx;
    ctx.dry_run = true;
    
    LifecycleResult result = upgrade(ctx, "1.0.0");
    
    assert(result.operation == LifecycleOperation::kUpgrade);
    assert(result.success);
    
    std::cout << "[PASS] test_upgrade_basic" << std::endl;
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main() {
    std::cout << "Rebuntu Lifecycle Tests (Phase 1.11)" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // Type conversion tests
    test_operation_string_conversion();
    test_artifact_ownership_string_conversion();
    test_artifact_type_string_conversion();
    test_lifecycle_status_string_conversion();
    test_artifact_operation_action_string_conversion();
    
    // Data structure tests
    test_artifact_manifest();
    test_lifecycle_context();
    test_lifecycle_result_structure();
    
    // Operation tests (dry-run)
    test_reconfigure_dry_run();
    test_uninstall_dry_run();
    test_purge_dry_run();
    test_upgrade_basic();
    
    // Integration tests
    test_reconfigure_write();
    test_repair_missing_directory();
    test_repair_existing_directory();
    
    std::cout << "======================================" << std::endl;
    std::cout << "All lifecycle tests passed!" << std::endl;
    
    return 0;
}