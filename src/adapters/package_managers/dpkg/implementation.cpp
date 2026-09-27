// rebuntu::adapters::package_managers::dpkg — DPKG Package Inventory Implementation (Phase 5.31)
//
// This module implements the dpkg-based package inventory provider:
//   - Reads package information from /var/lib/dpkg/status
//   - Observes: name, version, architecture, description, dependencies, state
//   - Provides bounded observation of installed packages

#include "adapters/package_managers/dpkg/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

namespace rebuntu::adapters::package_managers::dpkg {

// ============================================================================
// Helper: Split string into tokens by delimiter
// ============================================================================
static std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// ============================================================================
// Helper: Trim whitespace from string
// ============================================================================
static std::string trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(static_cast<unsigned char>(str[start]))) {
        start++;
    }
    
    if (start == str.length()) {
        return "";
    }
    
    size_t end = str.length();
    while (end > start && isspace(static_cast<unsigned char>(str[end - 1]))) {
        end--;
    }
    
    return str.substr(start, end - start);
}

// ============================================================================
// Helper: Parse version string (epoch:version-release)
// ============================================================================
static void parse_version(const std::string& version, PackageObservation& pkg) {
    // Format: [epoch:]version[-release]
    size_t colon_pos = version.find(':');
    if (colon_pos != std::string::npos) {
        pkg.epoch = version.substr(0, colon_pos);
    }
    
    // Get version part after epoch
    std::string version_part = (colon_pos != std::string::npos) ? 
        version.substr(colon_pos + 1) : version;
    
    // Split at '-' for release
    size_t dash_pos = version_part.find('-');
    if (dash_pos != std::string::npos) {
        pkg.version_num = version_part.substr(0, dash_pos);
        pkg.revision = version_part.substr(dash_pos + 1);
    } else {
        pkg.version_num = version_part;
    }
}

// ============================================================================
// Helper: Parse dpkg status string
//
// Format: "desired-state actual-state"
// e.g., "ii" = installed, installed
//       "ri" = remove awaiting, installed (to be removed)
//       "hi" = hold awaiting, installed
//       "ci" = config pending, installed
// ============================================================================
static void parse_status(const std::string& status, PackageStatus& pkg_status, 
                         PackageInstallState& install_state) {
    if (status.length() < 2) {
        pkg_status.desired_state = '?';
        pkg_status.actual_state = '?';
        install_state = PackageInstallState::kUnknown;
        return;
    }
    
    pkg_status.desired_state = status[0];
    pkg_status.actual_state = status[1];
    
    // Determine install state from actual state
    switch (status[1]) {
        case 'i':  // installed
            if (status[0] == 'i') {
                install_state = PackageInstallState::kInstalled;
            } else if (status[0] == 'r') {
                install_state = PackageInstallState::kHalfInstalled;  // awaiting removal
            } else if (status[0] == 'h') {
                install_state = PackageInstallState::kHalfInstalled;  // awaiting hold
            } else {
                install_state = PackageInstallState::kConfigFiles;
            }
            break;
        case 'h':  // half-installed
            install_state = PackageInstallState::kHalfInstalled;
            break;
        case 'u':  // unpacked
            install_state = PackageInstallState::kUnpacked;
            break;
        case 'f':  // config-files
            install_state = PackageInstallState::kConfigFiles;
            break;
        case 'W':  // wait
            install_state = PackageInstallState::kNotInstalled;
            break;
        default:
            install_state = PackageInstallState::kUnknown;
            break;
    }
}

// ============================================================================
// Helper: Split comma-separated dependencies
// ============================================================================
static std::vector<std::string> split_dependencies(const std::string& deps) {
    std::vector<std::string> result;
    
    // dpkg dependency format: pkg1 (>= 1.0), pkg2, pkg3 [!arch]
    // We'll extract just the package names
    std::istringstream stream(deps);
    std::string token;
    
    while (std::getline(stream, token, ',')) {
        // Extract package name (remove version constraints and arch qualifiers)
        size_t space_pos = token.find(' ');
        if (space_pos != std::string::npos) {
            result.push_back(trim(token.substr(0, space_pos)));
        } else {
            // Remove arch qualifier like [!amd64]
            size_t bracket_pos = token.find('[');
            if (bracket_pos != std::string::npos) {
                result.push_back(trim(token.substr(0, bracket_pos)));
            } else {
                result.push_back(trim(token));
            }
        }
    }
    
    return result;
}

// ============================================================================
// Helper: Parse a single package block
// ============================================================================
static PackageObservation parse_package_block(const std::string& block) {
    PackageObservation pkg;
    
    std::istringstream stream(block);
    std::string line;
    
    while (std::getline(stream, line)) {
        // Handle continuation lines (starting with space)
        if (!line.empty() && (line[0] == ' ' || line[0] == '\t')) {
            // Continuation of previous field - append to last added field
            continue;
        }
        
        // Parse key: value format
        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) {
            continue;
        }
        
        std::string key = trim(line.substr(0, colon_pos));
        std::string value = trim(line.substr(colon_pos + 1));
        
        if (key == "Package") {
            pkg.identity.name = value;
        } else if (key == "Architecture") {
            pkg.identity.architecture = value;
        } else if (key == "Version") {
            pkg.version = value;
            // Parse epoch:version-release format
            parse_version(value, pkg);
        } else if (key == "Description") {
            pkg.description = value;
        } else if (key == "Long-Description") {
            pkg.long_description = value;
        } else if (key == "Status") {
            parse_status(value, pkg.status, pkg.install_state);
        } else if (key == "Depends") {
            pkg.depends = split_dependencies(value);
        } else if (key == "Recommends") {
            pkg.recommends = split_dependencies(value);
        } else if (key == "Suggests") {
            pkg.suggests = split_dependencies(value);
        } else if (key == "Conflicts") {
            pkg.conflicts = split_dependencies(value);
        } else if (key == "Breaks") {
            pkg.breaks = split_dependencies(value);
        } else if (key == "Replaces") {
            pkg.replaces = split_dependencies(value);
        } else if (key == "Section") {
            // Split section by space
            std::istringstream iss(value);
            std::string sec;
            while (iss >> sec) {
                pkg.section.push_back(sec);
            }
        } else if (key == "Installed-Size") {
            try {
                uint64_t size_bytes = std::stoull(value);
                pkg.installed_size_kb = size_bytes / 1024; // Convert bytes to KB
            } catch (...) {}
        }
    }
    
    pkg.observed_at = std::chrono::system_clock::now();
    pkg.source = "dpkg";
    
    return pkg;
}

// ============================================================================
// Helper: Parse dpkg status file
//
// Format:
//   Package: package-name
//   Status: desired-state actual-state
//   Version: 1.2.3-4
//   Architecture: amd64
//   Description: short description
//    Long-Description: extended description
//   Depends: pkg1, pkg2 (>= 1.0), ...
//   Recommends: ...
//   Suggests: ...
//   Conflicts: ...
//   Breaks: ...
//   Replaces: ...
//   Section: section-name
//   Installed-Size: size-in-KB
//   
// Each package is separated by a blank line.
// ============================================================================
static std::vector<PackageObservation> parse_dpkg_status(const std::string& status_content) {
    std::vector<PackageObservation> packages;
    
    // Split into package entries (separated by double newline)
    std::istringstream stream(status_content);
    std::string line;
    std::string current_package_block;
    
    while (std::getline(stream, line)) {
        if (line.empty() && !current_package_block.empty()) {
            // End of a package block - parse it
            PackageObservation pkg = parse_package_block(current_package_block);
            if (pkg.identity.is_valid()) {
                packages.push_back(std::move(pkg));
            }
            current_package_block.clear();
        } else if (!line.empty() || !current_package_block.empty()) {
            // Continue building the package block
            if (!current_package_block.empty() && line[0] != ' ' && line[0] != '\t') {
                // New field (not a continuation)
                current_package_block += "\n";
            }
            current_package_block += line;
        }
    }
    
    // Parse last block if any
    if (!current_package_block.empty()) {
        PackageObservation pkg = parse_package_block(current_package_block);
        if (pkg.identity.is_valid()) {
            packages.push_back(std::move(pkg));
        }
    }
    
    // Sort by package name for deterministic iteration
    std::sort(packages.begin(), packages.end(),
        [](const PackageObservation& a, const PackageObservation& b) {
            return a.identity.name < b.identity.name;
        });
    
    return packages;
}

// ============================================================================
// DpkgPackageInventoryAdapter Implementation
// ============================================================================

class DpkgPackageInventoryAdapter : public PackageInventoryAdapter {
public:
    DpkgPackageInventoryAdapter() = default;
    ~DpkgPackageInventoryAdapter() override = default;
    
    PackageInventoryResult observe_all_packages() override {
        PackageInventoryResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Read /var/lib/dpkg/status file
        std::string status_content;
        if (!read_dpkg_status(status_content)) {
            result.status = core::SemanticStatus::kUnknown;
            result.description = "Failed to read dpkg status file";
            result.fatal_error = core::Error{
                "E_DPKG_STATUS_READ",
                "Unable to read /var/lib/dpkg/status"
            };
            return result;
        }
        
        // Parse package entries
        packages_ = parse_dpkg_status(status_content);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        // Populate result
        result.packages = packages_;
        result.total_packages = packages_.size();
        
        for (const auto& pkg : packages_) {
            if (pkg.install_state == PackageInstallState::kInstalled) {
                result.installed_packages++;
            }
        }
        
        result.provider_source = "dpkg";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully discovered installed packages from dpkg";
        
        // Cache the observation time
        last_observation_time_ = result.observed_at;
        
        return result;
    }
    
    std::optional<PackageObservation> observe_package(const PackageIdentity& identity) override {
        auto it = std::find_if(packages_.begin(), packages_.end(),
            [&identity](const PackageObservation& pkg) {
                return pkg.identity.name == identity.name && 
                       pkg.identity.architecture == identity.architecture;
            });
        
        if (it != packages_.end()) {
            return *it;
        }
        
        // If not in cache, try to read directly from dpkg
        std::string status_content;
        if (!read_dpkg_status(status_content)) {
            return std::nullopt;
        }
        
        auto all_packages = parse_dpkg_status(status_content);
        auto it2 = std::find_if(all_packages.begin(), all_packages.end(),
            [&identity](const PackageObservation& pkg) {
                return pkg.identity.name == identity.name && 
                       pkg.identity.architecture == identity.architecture;
            });
        
        if (it2 != all_packages.end()) {
            packages_ = std::move(all_packages);
            last_observation_time_ = std::chrono::system_clock::now();
            return *it2;
        }
        
        return std::nullopt;
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }
    
    PackageInventoryResult force_refresh() override {
        // Clear cache and perform fresh observation
        packages_.clear();
        last_observation_time_ = {};
        return observe_all_packages();
    }

private:
    std::vector<PackageObservation> packages_;
    std::chrono::system_clock::time_point last_observation_time_{};
    
    static bool read_dpkg_status(std::string& content) {
        std::ifstream file("/var/lib/dpkg/status");
        if (!file.is_open()) {
            return false;
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        
        return !content.empty();
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<PackageInventoryAdapter> make_dpkg_package_inventory_adapter() {
    return std::make_unique<DpkgPackageInventoryAdapter>();
}

}  // namespace rebuntu::adapters::package_managers::dpkg