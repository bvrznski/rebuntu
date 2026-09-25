// rebuntu::infrastructure::container_runtime — Generalized Container Runtime Contracts (Phase 3.6)
//
// This header establishes Rebuntu's typed interface for container runtime integration
// that generalizes beyond Docker to support multiple container runtimes.
//
// Architecture:
//   Interfaces (what)        -> src/interfaces/
//   Adapters/Providers (how) -> cpp/src/adapters/container/
//
// Key principles:
//   * PROVIDER != CAPABILITY != OPERATION != SERVICE
//   * Container runtimes are OPTIONAL infrastructure (not a production dependency)
//   * No arbitrary shell strings - use structured argv for CLI tools
//   * CPU-only execution by default (GPU use requires explicit enablement)

#pragma once

#include <system/core/contracts.hpp>
#include <system/infrastructure/contracts.hpp>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// Container Runtime Identity
// ============================================================================

struct ContainerProviderId {
    std::string value;
    
    explicit ContainerProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const ContainerProviderId& a, const ContainerProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const ContainerProviderId& a, const ContainerProviderId& b) {
    return !(a == b);
}

// ============================================================================
// Container State
// ============================================================================

enum class ContainerState {
    kCreated,     // Container created but not started
    kRunning,     // Container is running
    kPaused,      // Container is paused
    kStopped,     // Container stopped/exited
    kDead,        // Container crashed or was killed
    kUnknown,     // State unknown
};

inline std::string_view to_string(ContainerState s) {
    switch (s) {
        case ContainerState::kCreated: return "created";
        case ContainerState::kRunning: return "running";
        case ContainerState::kPaused:  return "paused";
        case ContainerState::kStopped: return "stopped";
        case ContainerState::kDead:    return "dead";
        case ContainerState::kUnknown: return "unknown";
    }
    return "unknown";
}

// ============================================================================
// Container Information
// ============================================================================

struct ContainerInfo {
    std::string id;              // Container ID (full or truncated)
    std::string name;            // Container name
    std::string image;           // Image name with tag
    ContainerState state = ContainerState::kUnknown;  // Current state
    bool is_running = false;
    
    // Resource usage (if available)
    std::optional<uint64_t> memory_usage_bytes;
    std::optional<double> cpu_percent;
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> finished_at;
};

// ============================================================================
// Container Image Information
// ============================================================================

struct ImageInfo {
    std::string id;              // Image ID (digest)
    std::string repository;      // Repository name
    std::string tag;             // Tag (e.g., "latest")
    uint64_t size_bytes = 0;
    
    std::optional<std::chrono::system_clock::time_point> created_at;
};

// ============================================================================
// Container Provider Result Types
// ============================================================================

struct ContainerResult {
    core::SemanticStatus status;
    
    // Operation that was performed (for verification)
    std::optional<std::string> operation_id;
    
    // Data returned from the operation (where applicable)
    std::vector<ContainerInfo> containers;
    std::vector<ImageInfo> images;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    static ContainerResult success() {
        ContainerResult r;
        r.status = core::SemanticStatus::kSuccess;
        return r;
    }
    
    static ContainerResult success_with_containers(std::vector<ContainerInfo> containers) {
        ContainerResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.containers = std::move(containers);
        return r;
    }
    
    static ContainerResult success_with_images(std::vector<ImageInfo> images) {
        ContainerResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.images = std::move(images);
        return r;
    }
    
    static ContainerResult failure(std::string code, std::string message) {
        ContainerResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static ContainerResult unavailable(std::string message) {
        ContainerResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_CONTAINER_UNAVAILABLE", std::move(message)};
        return r;
    }
};

// ============================================================================
// Container Provider Interface
// ============================================================================

class ContainerProvider {
public:
    virtual ~ContainerProvider() = default;
    
    // Get provider type (for registry selection)
    virtual ProviderType provider_type() const = 0;
    
    // Get provider identity
    virtual ContainerProviderId provider_id() const = 0;
    
    // Check if container runtime is available and accessible
    virtual bool is_available() const = 0;
    
    // Get container runtime version information
    virtual std::optional<std::string> get_version() const = 0;
    
    // List containers (optionally filtered by state)
    virtual ContainerResult list_containers(
        const std::vector<ContainerState>& states,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Get container details by ID or name
    virtual ContainerResult inspect_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // List images
    virtual ContainerResult list_images(
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Pull an image from a registry
    virtual ContainerResult pull_image(
        const std::string& image_ref,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Get image details by ID or name
    virtual ContainerResult inspect_image(
        const std::string& image_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Start a container
    virtual ContainerResult start_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Stop a running container
    virtual ContainerResult stop_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Remove a container (force removal if it's running)
    virtual ContainerResult remove_container(
        const std::string& container_id_or_name,
        bool force = false,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Run a new container with options
    virtual ContainerResult run_container(
        const std::string& image_ref,
        const std::vector<std::string>& command,
        const std::vector<std::string>& env_vars,
        const std::vector<std::pair<std::string, std::string>>& mounts,
        bool cpu_only = true,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
};

// ============================================================================
// Container Provider Registry (for multi-runtime support)
// ============================================================================

class ContainerProviderRegistry {
public:
    // Register a container provider
    void register_provider(std::unique_ptr<ContainerProvider> provider);
    
    // Get available provider for given type, or nullptr if none available
    std::optional<ContainerProvider*> get_provider(ProviderType type) const;
    
    // List all registered providers
    std::vector<ContainerProvider*> all_providers() const;
    
    // Convenience methods that select from available providers
    ContainerResult list_containers(
        const std::vector<ContainerState>& states,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;
    
    ContainerResult inspect_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;
    
    ContainerResult list_images(
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;
    
    ContainerResult pull_image(
        const std::string& image_ref,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;
    
    ContainerResult inspect_image(
        const std::string& image_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;
    
    ContainerResult start_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;
    
    ContainerResult stop_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;
    
    ContainerResult remove_container(
        const std::string& container_id_or_name,
        bool force = false,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const;

private:
    std::map<ProviderType, std::unique_ptr<ContainerProvider>> providers_;
};

// ============================================================================
// CLI Provider Base (common subprocess execution utilities)
// ============================================================================

namespace container_cli {

// Configuration for container provider
struct Config {
    std::optional<std::string> cli_path;  // Path to CLI executable (default: discover via PATH)
    bool cpu_only = true;                  // CPU-only execution (policy)
};

}  // namespace container_cli

}  // namespace rebuntu::infrastructure

// ============================================================================
// Hash support for ContainerProviderId
// ============================================================================

namespace std {
template <> struct hash<rebuntu::infrastructure::ContainerProviderId> {
    size_t operator()(const rebuntu::infrastructure::ContainerProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}  // namespace std