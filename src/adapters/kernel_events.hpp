// rebuntu::adapters::kernel_events — Native Linux Event Adapters (Phase 4.17)
//
// This module provides adapters that connect native Linux kernel events
// to Rebuntu's activation engine.
//
// Native Event Sources:
//   - udev/netlink: Device add/remove events
//   - systemd D-Bus signals: Service state changes, unit events
//   - inotify: Filesystem change events

#pragma once

#include <runtime/contracts.hpp>

#include <memory>
#include <string>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <optional>

namespace rebuntu::events {
class ActivationEngine;
}

namespace rebuntu::adapters {

// ============================================================================
// EventSourceAdapter
// ============================================================================

template<typename ConfigType>
class EventSourceAdapter {
public:
    using Config = ConfigType;
    
    virtual ~EventSourceAdapter() = default;
    
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    virtual const Config& config() const = 0;
    virtual bool is_running() const = 0;
};

// ============================================================================
// UdevNetlinkAdapter
// ============================================================================

struct UdevConfig {
    std::string socket_path = "/run/udev/control";
    int buffer_size = 8192;
    bool subscribe_device_events = true;
    bool subscribe_block_events = false;
};

class UdevNetlinkAdapter : public EventSourceAdapter<UdevConfig> {
public:
    using OnEventCallback = std::function<void(const runtime::Event&)>;
    
    explicit UdevNetlinkAdapter(
        const UdevConfig& config,
        OnEventCallback callback);
    
    ~UdevNetlinkAdapter() override;
    
    core::Outcome start() override;
    core::Outcome stop() override;
    
    const UdevConfig& config() const override { return config_; }
    bool is_running() const override { return running_; }
    
    static runtime::Event convert_udev_event(
        const std::string& action,
        const std::string& devpath,
        const std::string& subsystem,
        const std::unordered_map<std::string, std::string>& env);
    
private:
    UdevConfig config_;
    OnEventCallback callback_;
    bool running_ = false;
    int socket_fd_ = -1;
};

// ============================================================================
// SystemdSignalAdapter
// ============================================================================

struct SystemdConfig {
    std::string bus_address;
    std::chrono::milliseconds timeout_ms{5000};
    bool watch_services = true;
    bool watch_units = true;
};

class SystemdSignalAdapter : public EventSourceAdapter<SystemdConfig> {
public:
    using OnEventCallback = std::function<void(const runtime::Event&)>;
    
    explicit SystemdSignalAdapter(
        const SystemdConfig& config,
        OnEventCallback callback);
    
    ~SystemdSignalAdapter() override;
    
    core::Outcome start() override;
    core::Outcome stop() override;
    
    const SystemdConfig& config() const override { return config_; }
    bool is_running() const override { return running_; }
    
    static runtime::Event convert_systemd_signal(
        const std::string& signal_name,
        const std::string& unit_path,
        const std::vector<std::pair<std::string, std::string>>& details);
    
private:
    SystemdConfig config_;
    OnEventCallback callback_;
    bool running_ = false;
    int signal_subscription_id_ = -1;
};

// ============================================================================
// InotifyAdapter
// ============================================================================

struct InotifyConfig {
    std::vector<std::string> watch_paths;
    int max_events_per_batch = 100;
    std::chrono::milliseconds debounce_timeout_ms{100};
};

class InotifyAdapter : public EventSourceAdapter<InotifyConfig> {
public:
    using OnEventCallback = std::function<void(const runtime::Event&)>;
    
    explicit InotifyAdapter(
        const InotifyConfig& config,
        OnEventCallback callback);
    
    ~InotifyAdapter() override;
    
    core::Outcome start() override;
    core::Outcome stop() override;
    
    const InotifyConfig& config() const override { return config_; }
    bool is_running() const override { return running_; }
    
    static runtime::Event convert_inotify_event(
        int wd,
        uint32_t mask,
        const std::string& filename);
    
private:
    InotifyConfig config_;
    OnEventCallback callback_;
    bool running_ = false;
    int inotify_fd_ = -1;
    std::vector<int> watch_descriptors_;
};

// ============================================================================
// NativeEventChain
// ============================================================================

struct NativeEventChain {
    static core::Outcome create_chain(
        const std::vector<std::string>& watch_paths,
        std::shared_ptr<events::ActivationEngine> engine,
        std::chrono::milliseconds event_timeout_ms);
    
    static size_t process_batch(
        std::shared_ptr<events::ActivationEngine> engine,
        std::chrono::milliseconds timeout);
    
    struct Metrics {
        size_t events_received = 0;
        size_t activations_triggered = 0;
        size_t events_suppressed = 0;
    };
    static Metrics get_metrics();
};

// ============================================================================
// Factory Functions
// ============================================================================

inline std::unique_ptr<UdevNetlinkAdapter> make_udev_adapter(
    const UdevConfig& config,
    UdevNetlinkAdapter::OnEventCallback callback) {
    return std::make_unique<UdevNetlinkAdapter>(config, std::move(callback));
}

inline std::unique_ptr<SystemdSignalAdapter> make_systemd_adapter(
    const SystemdConfig& config,
    SystemdSignalAdapter::OnEventCallback callback) {
    return std::make_unique<SystemdSignalAdapter>(config, std::move(callback));
}

inline std::unique_ptr<InotifyAdapter> make_inotify_adapter(
    const InotifyConfig& config,
    InotifyAdapter::OnEventCallback callback) {
    return std::make_unique<InotifyAdapter>(config, std::move(callback));
}

}  // namespace rebuntu::adapters