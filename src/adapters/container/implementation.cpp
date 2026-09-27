// rebuntu::adapters::container — Container Runtime Discovery Implementation (Phase 5.30)
//
// This module implements Rebuntu's container/runtime boundary discovery:
//   - Detects containerized environments only from reliable evidence
//   - Does NOT equate cgroup path substrings with definitive identity without validation

#include "adapters/container/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstring>
#include <dirent.h>

namespace rebuntu::adapters::container {

// ============================================================================
// Helper: Read file line (trims trailing whitespace)
// ============================================================================
static std::string read_file_line(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    
    std::string line;
    if (std::getline(file, line)) {
        // Trim trailing whitespace
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        return line;
    }
    
    return "";
}

// ============================================================================
// Helper: Read /proc/[pid]/cgroup for evidence
// Returns raw cgroup entries without inference
// ============================================================================
static std::vector<std::string> read_cgroup_entries(int pid) {
    std::vector<std::string> result;
    auto path = std::filesystem::path("/proc") / std::to_string(pid) / "cgroup";
    
    std::ifstream file(path);
    if (!file.is_open()) {
        return result;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Format: 0::/init.scope
        // We just capture the raw path part for evidence
        size_t pos = line.rfind('/');
        if (pos != std::string::npos) {
            result.push_back(line.substr(pos));
        }
    }
    
    return result;
}

// ============================================================================
// Helper: Read /proc/[pid]/environ for environment variables
// Returns vector of key=value strings
// ============================================================================
static std::vector<std::string> read_env_vars(int pid) {
    std::vector<std::string> result;
    auto path = std::filesystem::path("/proc") / std::to_string(pid) / "environ";
    
    std::ifstream file(path);
    if (!file.is_open()) {
        return result;
    }
    
    std::string entry;
    char c;
    while (file.get(c)) {
        if (c == '\0') {
            if (!entry.empty()) {
                result.push_back(entry);
                entry.clear();
            }
        } else {
            entry += c;
        }
    }
    
    return result;
}

// Helper: Read mountinfo for filesystem evidence (reserved for future use)

// ============================================================================
// Helper: Read DMI product name for virtualization detection
// ============================================================================
static std::optional<std::string> read_dmi_product_name() {
    static const std::vector<std::string> dmi_paths = {
        "/sys/class/dmi/id/product_name",
        "/sys/class/dmi/id/chassis_type"
    };
    
    for (const auto& path : dmi_paths) {
        if (std::filesystem::exists(path)) {
            return read_file_line(path);
        }
    }
    return std::nullopt;
}

// ============================================================================
// ContainerDiscoveryAdapterImpl
// ============================================================================
class ContainerDiscoveryAdapterImpl : public ContainerDiscoveryAdapter {
public:
    ContainerDiscoveryAdapterImpl() = default;
    ~ContainerDiscoveryAdapterImpl() override = default;
    
    ContainerDiscoveryResult observe_container() override {
        ContainerDiscoveryResult result;
        auto start_time = std::chrono::steady_clock::now();
        
        // Collect evidence from all native sources
        collect_evidence(result);
        
        // Validate and infer runtime type only if we have sufficient evidence
        validate_evidence(result);
        
        auto end_time = std::chrono::steady_clock::now();
        result.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.captured_at = std::chrono::system_clock::now();
        
        if (result.is_container) {
            result.status = core::SemanticStatus::kSuccess;
            result.description = "Container detected: " + to_string(result.runtime_type);
        } else {
            result.status = core::SemanticStatus::kSuccess;
            result.description = "Not running in a container";
        }
        
        last_observation_time_ = result.captured_at;
        cached_result_ = result;
        
        return result;
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }
    
    ContainerDiscoveryResult force_refresh() override {
        return observe_container();
    }

private:
    std::chrono::system_clock::time_point last_observation_time_{};
    ContainerDiscoveryResult cached_result_{};
    
    void collect_evidence(ContainerDiscoveryResult& result) {
        // 1. Check for filesystem evidence (/.dockerenv, etc.)
        check_filesystem_evidence(result);
        
        // 2. Read cgroup entries
        check_cgroup_evidence(result);
        
        // 3. Read environment variables
        check_environ_evidence(result);
        
        // 4. Check DMI/sysfs for virtualization
        check_dmi_evidence(result);
    }
    
    void check_filesystem_evidence(ContainerDiscoveryResult& result) {
        ///.dockerenv file presence is strong Docker evidence
        if (std::filesystem::exists("/.dockerenv")) {
            ContainerEvidence e;
            e.source = EvidenceSource::kFileSystemEntry;
            e.key = "dockerenv_exists";
            e.value = "true";
            e.observed_at = std::chrono::system_clock::now();
            result.evidence.push_back(e);
            
            result.validation.has_filesystem_evidence = true;
        }
        
        // Check for /.podman-containers
        if (std::filesystem::exists("/.podman-containers")) {
            ContainerEvidence e;
            e.source = EvidenceSource::kFileSystemEntry;
            e.key = "podman_containers_exists";
            e.value = "true";
            e.observed_at = std::chrono::system_clock::now();
            result.evidence.push_back(e);
            
            result.validation.has_filesystem_evidence = true;
        }
        
        // Check for /.lxc
        if (std::filesystem::exists("/.lxc")) {
            ContainerEvidence e;
            e.source = EvidenceSource::kFileSystemEntry;
            e.key = "lxc_exists";
            e.value = "true";
            e.observed_at = std::chrono::system_clock::now();
            result.evidence.push_back(e);
            
            result.validation.has_filesystem_evidence = true;
        }
        
        // Check for /run/.containerenv (systemd-nspawn)
        if (std::filesystem::exists("/run/.containerenv")) {
            ContainerEvidence e;
            e.source = EvidenceSource::kFileSystemEntry;
            e.key = "containerenv_exists";
            e.value = "true";
            e.observed_at = std::chrono::system_clock::now();
            result.evidence.push_back(e);
            
            result.validation.has_filesystem_evidence = true;
        }
    }
    
    void check_cgroup_evidence(ContainerDiscoveryResult& result) {
        auto cgroups = read_cgroup_entries(1);  // PID 1
        
        if (!cgroups.empty()) {
            result.validation.has_cgroup_evidence = true;
            
            for (const auto& cg : cgroups) {
                ContainerEvidence e;
                e.source = EvidenceSource::kProcCgroup;
                e.key = "cgroup_entry";
                e.value = cg;
                e.observed_at = std::chrono::system_clock::now();
                result.evidence.push_back(e);
            }
        }
    }
    
    void check_environ_evidence(ContainerDiscoveryResult& result) {
        auto env_vars = read_env_vars(1);  // PID 1
        
        if (!env_vars.empty()) {
            result.validation.has_environ_evidence = true;
            
            for (const auto& ev : env_vars) {
                ContainerEvidence e;
                e.source = EvidenceSource::kProcEnviron;
                
                // Extract key and value
                size_t pos = ev.find('=');
                if (pos != std::string::npos) {
                    e.key = ev.substr(0, pos);
                    e.value = ev.substr(pos + 1);
                } else {
                    e.key = ev;
                    e.value = "";
                }
                
                e.observed_at = std::chrono::system_clock::now();
                result.evidence.push_back(e);
            }
        }
    }
    
    void check_dmi_evidence(ContainerDiscoveryResult& result) {
        auto product_name = read_dmi_product_name();
        
        if (product_name.has_value()) {
            result.validation.has_dmi_evidence = true;
            
            ContainerEvidence e;
            e.source = EvidenceSource::kSysClassDMI;
            e.key = "product_name";
            e.value = product_name.value();
            e.observed_at = std::chrono::system_clock::now();
            result.evidence.push_back(e);
        }
    }
    
    void validate_evidence(ContainerDiscoveryResult& result) {
        // Count different evidence types for confidence
        int evidence_count = 0;
        
        // Check for container filesystem markers
        for (const auto& e : result.evidence) {
            if (e.key == "dockerenv_exists") {
                result.runtime_type = ContainerRuntimeType::kDocker;
                result.is_container = true;
                evidence_count++;
                result.validation.validated_sources.push_back("docker:/.dockerenv");
            }
            if (e.key == "podman_containers_exists") {
                result.runtime_type = ContainerRuntimeType::kPodman;
                result.is_container = true;
                evidence_count++;
                result.validation.validated_sources.push_back("podman:/.podman-containers");
            }
            if (e.key == "lxc_exists") {
                result.runtime_type = ContainerRuntimeType::kLXC;
                result.is_container = true;
                evidence_count++;
                result.validation.validated_sources.push_back("lxc:/.lxc");
            }
            if (e.key == "containerenv_exists") {
                result.runtime_type = ContainerRuntimeType::kSystemdNspawn;
                result.is_container = true;
                evidence_count++;
                result.validation.validated_sources.push_back("systemd-nspawn:/run/.containerenv");
            }
        }
        
        // Check environment variables for container markers
        for (const auto& e : result.evidence) {
            if (e.key == "container" && 
                (e.value.find("docker") != std::string::npos ||
                 e.value.find("podman") != std::string::npos)) {
                result.is_container = true;
                evidence_count++;
                result.validation.validated_sources.push_back("environ:container=" + e.value);
            }
            
            // systemd-nspawn sets container_pid=1
            if (e.key == "container_pid" && e.value == "1") {
                result.runtime_type = ContainerRuntimeType::kSystemdNspawn;
                result.is_container = true;
                evidence_count++;
                result.validation.validated_sources.push_back("environ:container_pid=1");
            }
            
            // Podman sets PODMAN or CONTAINER_RUNTIME
            if (e.key == "PODMAN" || e.key == "CONTAINER_RUNTIME") {
                result.runtime_type = ContainerRuntimeType::kPodman;
                result.is_container = true;
                evidence_count++;
                result.validation.validated_sources.push_back("environ:" + e.key);
            }
        }
        
        // Check cgroup entries for container signatures
        for (const auto& e : result.evidence) {
            if (e.key == "cgroup_entry") {
                // Docker often has paths like /docker/ or /system.slice/...-container-*.scope
                // Podman: /user.slice/...-container-*.scope or /machine.slice/...-container-*.scope
                if (e.value.find("-container-") != std::string::npos) {
                    result.is_container = true;
                    evidence_count++;
                    // Don't assume which runtime - could be either
                }
            }
        }
        
        // Check DMI for virtualization hints
        for (const auto& e : result.evidence) {
            if (e.key == "product_name") {
                std::string val = e.value;
                // Docker Desktop uses Hyper-V sometimes, but we check for container-specific markers
                if (val.find("Docker") != std::string::npos ||
                    val.find("VirtualBox") != std::string::npos ||
                    val.find("VMware") != std::string::npos) {
                    result.validation.has_dmi_evidence = true;
                }
            }
        }
        
        // Final validation: We require at least ONE strong evidence source
        if (evidence_count > 0 && !result.is_container) {
            // Should not happen, but handle gracefully
            result.is_container = false;
            result.runtime_type = ContainerRuntimeType::kNone;
        }
    }
};

std::unique_ptr<ContainerDiscoveryAdapter> make_container_discovery_adapter() {
    return std::make_unique<ContainerDiscoveryAdapterImpl>();
}

}  // namespace rebuntu::adapters::container