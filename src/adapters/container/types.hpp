// rebuntu::adapters::container — Container Runtime Discovery Adapter (Phase 5.30)
//
// This module implements Rebuntu's container/runtime boundary discovery adapter:
//   - Detects containerized environments only from reliable evidence
//   - Does NOT equate cgroup path substrings with definitive identity without validation
//   - Provides typed evidence-based observations from native Linux sources
//
// Native Interfaces Used:
//   - /proc/1/cgroup — cgroup membership (raw observation, not inference)
//   - /proc/1/environ — environment variables (with provenance)
//   - /proc/self/mountinfo — filesystem mount evidence
//   - /sys/class/dmi/id/product_name — virtualization detection

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <chrono>
#include <vector>

namespace rebuntu::adapters::container {

enum class ContainerRuntimeType {
    kNone,
    kDocker,
    kPodman,
    kLXC,
    kSystemdNspawn,
};

inline std::string to_string(ContainerRuntimeType t) {
    switch (t) {
        case ContainerRuntimeType::kNone:         return "none";
        case ContainerRuntimeType::kDocker:       return "docker";
        case ContainerRuntimeType::kPodman:       return "podman";
        case ContainerRuntimeType::kLXC:          return "lxc";
        case ContainerRuntimeType::kSystemdNspawn:return "systemd-nspawn";
    }
    return "unknown";
}

enum class EvidenceSource {
    kProcCgroup,
    kProcEnviron,
    kProcMountinfo,
    kSysClassDMI,
    kFileSystemEntry,
};

inline std::string to_string(EvidenceSource s) {
    switch (s) {
        case EvidenceSource::kProcCgroup:     return "proc-cgroup";
        case EvidenceSource::kProcEnviron:    return "proc-environ";
        case EvidenceSource::kProcMountinfo:  return "proc-mountinfo";
        case EvidenceSource::kSysClassDMI:    return "sys-class-dmi";
        case EvidenceSource::kFileSystemEntry:return "filesystem-entry";
    }
    return "unknown";
}

struct ContainerEvidence {
    EvidenceSource source;
    std::string key;
    std::string value;
    std::chrono::system_clock::time_point observed_at{};
};

struct ValidationInfo {
    bool has_filesystem_evidence{false};
    bool has_cgroup_evidence{false};
    bool has_environ_evidence{false};
    bool has_dmi_evidence{false};
    std::vector<std::string> validated_sources;
};

struct ContainerDiscoveryResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description;
    
    bool is_container{false};
    ContainerRuntimeType runtime_type{ContainerRuntimeType::kNone};
    
    std::vector<ContainerEvidence> evidence;
    
    ValidationInfo validation;
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
    
    std::optional<core::Error> error;
};

class ContainerDiscoveryAdapter {
public:
    virtual ~ContainerDiscoveryAdapter() = default;
    
    virtual ContainerDiscoveryResult observe_container() = 0;
    
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    virtual ContainerDiscoveryResult force_refresh() = 0;
};

std::unique_ptr<ContainerDiscoveryAdapter> make_container_discovery_adapter();

}  // namespace rebuntu::adapters::container