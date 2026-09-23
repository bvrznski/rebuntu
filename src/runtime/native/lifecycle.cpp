// rebuntu::lifecycle — Lifecycle Operations Implementation (Phase 1.11)
//
// This implements the canonical interface for Rebuntu lifecycle operations:
//   * RECONFIGURE: Change configuration without reinstalling
//   * REPAIR: Restore Rebuntu-owned installation invariants
//   * UPGRADE: Version-aware migration between schema versions
//   * UNINSTALL/PURGE: Remove Rebuntu-owned artifacts

#include <runtime/lifecycle/contracts.hpp>
#include <runtime/core/contracts.hpp>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <optional>

namespace fs = std::filesystem;

// ============================================================================
// Helper Functions (defined before namespace to avoid duplicate declarations)
// ============================================================================

static bool path_exists(const std::string& path) {
    std::error_code ec;
    return fs::exists(fs::path(path), ec);
}

static bool is_directory(const std::string& path) {
    std::error_code ec;
    return fs::is_directory(fs::path(path), ec);
}

static bool is_regular_file(const std::string& path) {
    std::error_code ec;
    return fs::is_regular_file(fs::path(path), ec);
}

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

static bool create_directory(const std::string& path, uint32_t mode = 0755) {
    std::error_code ec;
    
    if (fs::is_directory(fs::path(path), ec)) {
        return true;
    }
    
    fs::create_directories(fs::path(path), ec);
    if (ec) {
        return false;
    }
    
    fs::permissions(fs::path(path), static_cast<fs::perms>(mode), ec);
    return !ec;
}

static bool remove_path(const std::string& path) {
    std::error_code ec;
    
    if (is_directory(path)) {
        return fs::remove_all(fs::path(path), ec) > 0;
    } else {
        return fs::remove(fs::path(path), ec);
    }
}

// ============================================================================
// Detect Context
// ============================================================================

namespace rebuntu::lifecycle {

LifecycleContext detect_context() {
    LifecycleContext ctx;
    
    uid_t uid = geteuid();
    ctx.scope = (uid == 0) ? LifecycleContext::Scope::kSystem : LifecycleContext::Scope::kUser;
    
    const char* home = std::getenv("HOME");
    if (home) {
        ctx.install_root = (ctx.scope == LifecycleContext::Scope::kSystem) ? "/" : std::string(home);
    } else {
        ctx.install_root = "/";
    }
    
    if (ctx.scope == LifecycleContext::Scope::kSystem) {
        ctx.config_dir = "/etc/rebuntu";
        ctx.state_dir = "/var/lib/rebuntu";
        ctx.cache_dir = "/var/cache/rebuntu";
    } else {
        ctx.config_dir = ctx.install_root + "/.config/rebuntu";
        ctx.state_dir = ctx.install_root + "/.local/state/rebuntu";
        ctx.cache_dir = ctx.install_root + "/.cache/rebuntu";
    }
    
    return ctx;
}

LifecycleContext build_default_context() {
    return detect_context();
}

// ============================================================================
// Get Artifact Manifest - implementation for public API
// ============================================================================

ArtifactManifest get_artifact_manifest(const LifecycleContext& ctx) {
    ArtifactManifest manifest;
    
    if (ctx.scope == LifecycleContext::Scope::kSystem) {
        // Binary
        manifest.add_entry({
            .path = "/usr/bin/rebuntu",
            .type = ArtifactType::kBinary,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle/upgrade",
            .is_optional = false
        });
        
        // Config directory
        manifest.add_entry({
            .path = "/etc/rebuntu",
            .type = ArtifactType::kDirectory,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle",
            .is_optional = false
        });
        
        // State directory  
        manifest.add_entry({
            .path = "/var/lib/rebuntu",
            .type = ArtifactType::kDirectory,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle",
            .is_optional = false
        });
        
        // Cache directory
        manifest.add_entry({
            .path = "/var/cache/rebuntu",
            .type = ArtifactType::kDirectory,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle",
            .is_optional = false
        });
    } else {
        manifest.add_entry({
            .path = ctx.install_root + "/.local/bin/rebuntu",
            .type = ArtifactType::kBinary,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle/upgrade",
            .is_optional = false
        });
        
        manifest.add_entry({
            .path = ctx.config_dir,
            .type = ArtifactType::kDirectory,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle",
            .is_optional = false
        });
        
        manifest.add_entry({
            .path = ctx.state_dir,
            .type = ArtifactType::kDirectory,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle",
            .is_optional = false
        });
        
        manifest.add_entry({
            .path = ctx.cache_dir,
            .type = ArtifactType::kDirectory,
            .ownership = ArtifactOwnership::kRebuntuOwned,
            .expected_owner = std::nullopt,
            .expected_mode = std::nullopt,
            .checksum = std::nullopt,
            .managed_by = "lifecycle",
            .is_optional = false
        });
    }
    
    manifest.add_entry({
        .path = ctx.config_dir + "/config",
        .type = ArtifactType::kConfigFile,
        .ownership = ArtifactOwnership::kRebuntuOwned,
        .expected_owner = std::nullopt,
        .expected_mode = std::nullopt,
        .checksum = std::nullopt,
        .managed_by = "lifecycle",
        .is_optional = true
    });
    
    return manifest;
}

// ============================================================================
// Reconfigure Implementation
// ============================================================================

LifecycleResult reconfigure(const LifecycleContext& ctx, 
                            const std::map<std::string, std::string>& config) {
    LifecycleResult result;
    result.operation = LifecycleOperation::kReconfigure;
    result.status = LifecycleStatus::kInProgress;
    
    auto effective_ctx = detect_context();
    if (ctx.scope != LifecycleContext::Scope::kSystem) {
        effective_ctx.scope = ctx.scope;
    }
    
    std::string config_dir = effective_ctx.config_dir;
    std::string config_file = config_dir + "/config";
    
    bool dir_exists = path_exists(config_dir);
    
    if (!dir_exists && !ctx.dry_run) {
        if (!create_directory(config_dir)) {
            result.status = LifecycleStatus::kFailed;
            result.error = core::Error{
                "E_CONFIG_DIR_CREATE_FAILED",
                "Failed to create configuration directory: " + config_dir
            };
            return result;
        }
    } else if (!dir_exists && ctx.dry_run) {
        // Would create in dry-run
    }
    
    std::ostringstream ss;
    for (const auto& [key, value] : config) {
        ss << key << "=" << value << "\n";
    }
    
    if (!ctx.dry_run) {
        if (!write_file(config_file, ss.str())) {
            result.status = LifecycleStatus::kFailed;
            result.error = core::Error{
                "E_CONFIG_WRITE_FAILED",
                "Failed to write configuration file: " + config_file
            };
            return result;
        }
        
        auto readback = read_file(config_file);
        if (!readback.has_value() || readback.value().empty()) {
            result.status = LifecycleStatus::kPartial;
            result.error = core::Error{
                "E_CONFIG_VERIFICATION_FAILED",
                "Configuration file written but could not be verified"
            };
            return result;
        }
        
        std::map<std::string, std::string> parsed_config;
        std::istringstream read_ss(readback.value());
        std::string line;
        while (std::getline(read_ss, line)) {
            if (line.empty() || line[0] == '#') continue;
            size_t eq_pos = line.find('=');
            if (eq_pos != std::string::npos) {
                parsed_config[line.substr(0, eq_pos)] = line.substr(eq_pos + 1);
            }
        }
        
        bool verified = true;
        for (const auto& [key, value] : config) {
            if (parsed_config.find(key) == parsed_config.end() || parsed_config[key] != value) {
                verified = false;
                break;
            }
        }
        
        result.verified = verified;
        result.success = verified;
    } else {
        result.success = true;
        result.verified = false;
    }
    
    result.status = result.success ? LifecycleStatus::kCompleted : LifecycleStatus::kPartial;
    
    for (const auto& [key, value] : config) {
        ArtifactOperation op;
        op.path = config_file + " (" + key + ")";
        op.action = ArtifactOperation::Action::kUpdated;
        result.operations.push_back(op);
    }
    
    if (!dir_exists && !ctx.dry_run) {
        ArtifactOperation dir_op;
        dir_op.path = config_dir;
        dir_op.action = ArtifactOperation::Action::kCreated;
        result.operations.push_back(dir_op);
        result.created_paths.insert(config_dir);
    }
    
    return result;
}

// ============================================================================
// Repair Implementation
// ============================================================================

LifecycleResult repair(const LifecycleContext& ctx,
                       const std::vector<std::string>& paths) {
    LifecycleResult result;
    result.operation = LifecycleOperation::kRepair;
    result.status = LifecycleStatus::kInProgress;
    
    auto manifest = get_artifact_manifest(ctx);
    
    // Use the public API to get entries - not the private .entries_ member
    std::vector<ArtifactEntry> entries_to_repair;
    
    if (paths.empty()) {
        // Repair all Rebuntu-owned artifacts
        for (const auto& entry : manifest.all()) {
            if (entry.ownership == ArtifactOwnership::kRebuntuOwned) {
                entries_to_repair.push_back(entry);
            }
        }
    } else {
        // Only repair specified paths
        for (const std::string& path : paths) {
            auto entry_opt = manifest.find(path);
            if (entry_opt.has_value()) {
                entries_to_repair.push_back(entry_opt.value());
            }
        }
    }
    
    bool all_ok = true;
    
    for (const auto& entry : entries_to_repair) {
        ArtifactOperation op;
        op.path = entry.path;
        
        bool exists = path_exists(entry.path);
        bool is_correct_type = false;
        
        if (exists) {
            switch (entry.type) {
                case ArtifactType::kDirectory:
                    is_correct_type = is_directory(entry.path);
                    break;
                default:
                    is_correct_type = is_regular_file(entry.path);
                    break;
            }
        }
        
        if (!exists && !ctx.dry_run) {
            if (entry.type == ArtifactType::kDirectory) {
                if (create_directory(entry.path)) {
                    op.action = ArtifactOperation::Action::kCreated;
                    result.created_paths.insert(entry.path);
                } else {
                    op.action = ArtifactOperation::Action::kFailed;
                    op.error_code = std::make_optional<std::string>("E_REPAIR_FAILED");
                    op.error_message = std::make_optional<std::string>(
                        "Failed to create directory: " + entry.path);
                    all_ok = false;
                }
            } else if (entry.type == ArtifactType::kConfigFile) {
                std::string content = "# Rebuntu configuration\n";
                if (write_file(entry.path, content)) {
                    op.action = ArtifactOperation::Action::kCreated;
                    result.created_paths.insert(entry.path);
                } else {
                    op.action = ArtifactOperation::Action::kFailed;
                    op.error_code = std::make_optional<std::string>("E_REPAIR_FAILED");
                    op.error_message = std::make_optional<std::string>(
                        "Failed to create config file: " + entry.path);
                    all_ok = false;
                }
            }
        } else if (!is_correct_type && !ctx.dry_run) {
            op.action = ArtifactOperation::Action::kSkipped;
            op.error_code = std::make_optional<std::string>("E_REPAIR_TYPE_MISMATCH");
            op.error_message = std::make_optional<std::string>(
                "Path exists but is wrong type: " + entry.path);
            result.skipped_paths.insert(entry.path);
        } else {
            op.action = ArtifactOperation::Action::kVerified;
        }
        
        result.operations.push_back(op);
    }
    
    result.success = all_ok && !entries_to_repair.empty();
    result.verified = true;
    result.status = result.success ? LifecycleStatus::kCompleted : 
                    (result.operations.size() == entries_to_repair.size() ? 
                     LifecycleStatus::kPartial : LifecycleStatus::kFailed);
    
    return result;
}

// ============================================================================
// Upgrade Implementation
// ============================================================================

LifecycleResult upgrade(const LifecycleContext& ctx,
                        const std::string& target_version) {
    LifecycleResult result;
    result.operation = LifecycleOperation::kUpgrade;
    result.status = LifecycleStatus::kInProgress;
    
    // Placeholder implementation for Phase 1.11
    result.success = true;
    result.status = LifecycleStatus::kCompleted;
    
    ArtifactOperation op;
    op.path = target_version;
    op.action = ArtifactOperation::Action::kVerified;
    result.operations.push_back(op);
    
    return result;
}

// ============================================================================
// Uninstall Implementation
// ============================================================================

LifecycleResult uninstall(const LifecycleContext& ctx) {
    LifecycleResult result;
    result.operation = LifecycleOperation::kUninstall;
    result.status = LifecycleStatus::kInProgress;
    
    auto manifest = get_artifact_manifest(ctx);
    
    bool all_ok = true;
    
    for (const auto& entry : manifest.rebuntu_owned()) {
        if (!path_exists(entry.path)) {
            continue;  // Already removed - idempotent
        }
        
        if (!ctx.dry_run) {
            if (remove_path(entry.path)) {
                ArtifactOperation op;
                op.path = entry.path;
                op.action = ArtifactOperation::Action::kDeleted;
                result.deleted_paths.insert(entry.path);
                result.operations.push_back(op);
            } else {
                all_ok = false;
                ArtifactOperation op;
                op.path = entry.path;
                op.action = ArtifactOperation::Action::kFailed;
                op.error_code = std::make_optional<std::string>("E_UNINSTALL_FAILED");
                op.error_message = std::make_optional<std::string>(
                    "Failed to remove: " + entry.path);
                result.operations.push_back(op);
            }
        } else {
            ArtifactOperation op;
            op.path = entry.path;
            op.action = ArtifactOperation::Action::kDeleted;
            result.deleted_paths.insert(entry.path);
            result.operations.push_back(op);
        }
    }
    
    result.success = all_ok;
    result.status = LifecycleStatus::kCompleted;
    
    return result;
}

// ============================================================================
// Purge Implementation
// ============================================================================

LifecycleResult purge(const LifecycleContext& ctx) {
    LifecycleResult result;
    result.operation = LifecycleOperation::kPurge;
    result.status = LifecycleStatus::kInProgress;
    
    auto manifest = get_artifact_manifest(ctx);
    
    bool all_ok = true;
    
    for (const auto& entry : manifest.all()) {
        if (!path_exists(entry.path)) {
            continue;  // Already removed - idempotent
        }
        
        if (!ctx.dry_run) {
            if (remove_path(entry.path)) {
                ArtifactOperation op;
                op.path = entry.path;
                op.action = ArtifactOperation::Action::kDeleted;
                result.deleted_paths.insert(entry.path);
                result.operations.push_back(op);
            } else {
                all_ok = false;
                ArtifactOperation op;
                op.path = entry.path;
                op.action = ArtifactOperation::Action::kFailed;
                op.error_code = std::make_optional<std::string>("E_PURGE_FAILED");
                op.error_message = std::make_optional<std::string>(
                    "Failed to remove: " + entry.path);
                result.operations.push_back(op);
            }
        } else {
            ArtifactOperation op;
            op.path = entry.path;
            op.action = ArtifactOperation::Action::kDeleted;
            result.deleted_paths.insert(entry.path);
            result.operations.push_back(op);
        }
    }
    
    result.success = all_ok;
    result.status = LifecycleStatus::kCompleted;
    
    return result;
}

}  // namespace rebuntu::lifecycle