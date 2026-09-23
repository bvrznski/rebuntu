// rebuntu::infrastructure::docker — Docker Provider Contracts (Phase 3.5)
//
// This header establishes Rebuntu's typed interface for Docker container runtime
// integration. It defines what a Docker provider MUST implement without dictating HOW.
//
// Architecture:
//   Interfaces (what)        -> src/interfaces/
//   Adapters/Providers (how) -> cpp/src/adapters/docker/
//
// Key principles:
//   * PROVIDER != CAPABILITY != OPERATION != SERVICE
//   * Docker is OPTIONAL infrastructure (not a production dependency)
//   * No arbitrary shell strings - use structured argv for docker CLI
//   * CPU-only execution by default (GPU use requires explicit enablement)

#pragma once

#include <runtime/core/contracts.hpp>
#include <domains/development/infrastructure/contracts.hpp>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// Docker Provider Identity
// ============================================================================

struct DockerProviderId {
    std::string value;
    
    explicit DockerProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const DockerProviderId& a, const DockerProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const DockerProviderId& a, const DockerProviderId& b) {
    return !(a == b);
}

// ============================================================================
// Docker Container State
// ============================================================================

enum class DockerContainerState {
    kCreated,     // Container created but not started
    kRunning,     // Container is running
    kPaused,      // Container is paused
    kRestarting,  // Container is restarting
    kExited,      // Container exited normally
    kDead,        // Container crashed or was killed
    kUnknown,     // State unknown
};

inline std::string_view to_string(DockerContainerState s) {
    switch (s) {
        case DockerContainerState::kCreated:   return "created";
        case DockerContainerState::kRunning:   return "running";
        case DockerContainerState::kPaused:    return "paused";
        case DockerContainerState::kRestarting:return "restarting";
        case DockerContainerState::kExited:    return "exited";
        case DockerContainerState::kDead:      return "dead";
        case DockerContainerState::kUnknown:   return "unknown";
    }
    return "unknown";
}

// ============================================================================
// Container Information
// ============================================================================

struct DockerContainerInfo {
    std::string id;              // Container ID (full or truncated)
    std::string name;            // Container name
    std::string image;           // Image name with tag
    DockerContainerState state;  // Current state
    bool is_running = false;
    
    // Resource usage (if available)
    std::optional<uint64_t> memory_usage_bytes;
    std::optional<double> cpu_percent;
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> finished_at;
};

// ============================================================================
// Docker Image Information
// ============================================================================

struct DockerImageInfo {
    std::string id;              // Image ID (digest)
    std::string repository;      // Repository name
    std::string tag;             // Tag (e.g., "latest")
    uint64_t size_bytes = 0;
    
    std::optional<std::chrono::system_clock::time_point> created_at;
};

// ============================================================================
// Docker Provider Result Types
// ============================================================================

struct DockerResult {
    core::SemanticStatus status;
    
    // Operation that was performed (for verification)
    std::optional<std::string> operation_id;
    
    // Data returned from the operation (where applicable)
    std::vector<DockerContainerInfo> containers;
    std::vector<DockerImageInfo> images;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    static DockerResult success() {
        DockerResult r;
        r.status = core::SemanticStatus::kSuccess;
        return r;
    }
    
    static DockerResult success_with_containers(std::vector<DockerContainerInfo> containers) {
        DockerResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.containers = std::move(containers);
        return r;
    }
    
    static DockerResult success_with_images(std::vector<DockerImageInfo> images) {
        DockerResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.images = std::move(images);
        return r;
    }
    
    static DockerResult failure(std::string code, std::string message) {
        DockerResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static DockerResult unavailable(std::string message) {
        DockerResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_DOCKER_UNAVAILABLE", std::move(message)};
        return r;
    }
};

// ============================================================================
// Docker Provider Interface
// ============================================================================

class DockerProvider {
public:
    virtual ~DockerProvider() = default;
    
    // Get provider identity
    virtual DockerProviderId provider_id() const = 0;
    
    // Check if Docker is available and accessible
    virtual bool is_available() const = 0;
    
    // Get Docker server version information
    virtual std::optional<std::string> get_version() const = 0;
    
    // List containers (optionally filtered by state)
    virtual DockerResult list_containers(
        const std::vector<DockerContainerState>& states,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Get container details by ID or name
    virtual DockerResult inspect_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // List images
    virtual DockerResult list_images(
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Get image details by ID or name
    virtual DockerResult inspect_image(
        const std::string& image_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Start a container
    virtual DockerResult start_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Stop a running container
    virtual DockerResult stop_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Remove a container (force removal if it's running)
    virtual DockerResult remove_container(
        const std::string& container_id_or_name,
        bool force = false,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
};

// ============================================================================
// Native CLI Provider (Docker CLI wrapper using native subprocess)
// ============================================================================

namespace docker_cli {

// Configuration for the Docker provider
struct Config {
    std::optional<std::string> cli_path;  // Path to docker executable (default: discover via PATH)
    bool cpu_only = true;                  // CPU-only execution (policy)
};

// The Docker CLI provider wraps the docker command-line interface
class Provider : public DockerProvider {
public:
    explicit Provider(Config config);
    ~Provider() override;
    
    // Disable copy/move for resource management
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;
    
    // DockerProvider interface
    DockerProviderId provider_id() const override;
    bool is_available() const override;
    std::optional<std::string> get_version() const override;
    
    DockerResult list_containers(
        const std::vector<DockerContainerState>& states,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    DockerResult inspect_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    DockerResult list_images(
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    DockerResult inspect_image(
        const std::string& image_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    DockerResult start_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    DockerResult stop_container(
        const std::string& container_id_or_name,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    DockerResult remove_container(
        const std::string& container_id_or_name,
        bool force = false,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

}  // namespace docker_cli

}  // namespace rebuntu::infrastructure

// ============================================================================
// Hash support for DockerProviderId
// ============================================================================

namespace std {
template <> struct hash<rebuntu::infrastructure::DockerProviderId> {
    size_t operator()(const rebuntu::infrastructure::DockerProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}  // namespace std