// rebuntu::adapters::kernel_events — Native Linux Event Adapters Implementation (Phase 4.17)
//
// This module provides adapters that connect native Linux kernel events
// to Rebuntu's activation engine.

#include "adapters/kernel_events.hpp"

#include <unistd.h>
#include <sys/inotify.h>
#include <string.h>

namespace rebuntu::adapters {

// ============================================================================
// UdevNetlinkAdapter Implementation
// ============================================================================

UdevNetlinkAdapter::UdevNetlinkAdapter(
    const UdevConfig& config,
    OnEventCallback callback)
    : config_(config), callback_(std::move(callback)) {}

UdevNetlinkAdapter::~UdevNetlinkAdapter() {
    stop();
}

core::Outcome UdevNetlinkAdapter::start() {
    if (running_) {
        return core::Outcome::failure("E_ALREADY_STARTED", "Adapter already running");
    }
    
    // In a full implementation, this would:
    // 1. Open netlink socket for udev events
    // 2. Subscribe to device and block event types
    // 3. Start polling/reading events
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome UdevNetlinkAdapter::stop() {
    if (!running_) {
        return core::Outcome::failure("E_NOT_RUNNING", "Adapter not running");
    }
    
    running_ = false;
    return core::Outcome::success();
}

runtime::Event UdevNetlinkAdapter::convert_udev_event(
    const std::string& action,
    const std::string& devpath,
    const std::string& subsystem,
    const std::unordered_map<std::string, std::string>& env) {
    
    runtime::Event event;
    event.id = "udev-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "udev";
    event.type = action;
    
    // Add evidence with udev event data
    core::Evidence e1;
    e1.source = "udev_netlink";
    e1.value = action;
    event.evidence.push_back(e1);
    
    core::Evidence e2;
    e2.source = "udev_netlink";
    e2.value = devpath;
    event.evidence.push_back(e2);
    
    core::Evidence e3;
    e3.source = "udev_netlink";
    e3.value = subsystem;
    event.evidence.push_back(e3);
    
    for (const auto& [key, value] : env) {
        core::Evidence ev;
        ev.source = "udev_env";
        ev.value = key + "=" + value;
        event.evidence.push_back(ev);
    }
    
    return event;
}

// ============================================================================
// SystemdSignalAdapter Implementation
// ============================================================================

SystemdSignalAdapter::SystemdSignalAdapter(
    const SystemdConfig& config,
    OnEventCallback callback)
    : config_(config), callback_(std::move(callback)) {}

SystemdSignalAdapter::~SystemdSignalAdapter() {
    stop();
}

core::Outcome SystemdSignalAdapter::start() {
    if (running_) {
        return core::Outcome::failure("E_ALREADY_STARTED", "Adapter already running");
    }
    
    // In a full implementation, this would:
    // 1. Connect to systemd D-Bus system bus
    // 2. Subscribe to unit and service signals
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome SystemdSignalAdapter::stop() {
    if (!running_) {
        return core::Outcome::failure("E_NOT_RUNNING", "Adapter not running");
    }
    
    running_ = false;
    return core::Outcome::success();
}

runtime::Event SystemdSignalAdapter::convert_systemd_signal(
    const std::string& signal_name,
    const std::string& unit_path,
    const std::vector<std::pair<std::string, std::string>>& details) {
    
    runtime::Event event;
    event.id = "systemd-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "systemd";
    event.type = signal_name;
    
    core::Evidence e1;
    e1.source = "systemd_dbus";
    e1.value = unit_path;
    event.evidence.push_back(e1);
    
    for (size_t i = 0; i < details.size(); ++i) {
        const auto& [key, value] = details[i];
        core::Evidence ev;
        ev.source = "systemd_signal";
        ev.value = key + "=" + value;
        event.evidence.push_back(ev);
    }
    
    return event;
}

// ============================================================================
// InotifyAdapter Implementation
// ============================================================================

InotifyAdapter::InotifyAdapter(
    const InotifyConfig& config,
    OnEventCallback callback)
    : config_(config), callback_(std::move(callback)) {}

InotifyAdapter::~InotifyAdapter() {
    stop();
}

core::Outcome InotifyAdapter::start() {
    if (running_) {
        return core::Outcome::failure("E_ALREADY_STARTED", "Adapter already running");
    }
    
    inotify_fd_ = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    if (inotify_fd_ < 0) {
        return core::Outcome::failure(
            "E_INOTIFY_INIT_FAILED",
            "Failed to initialize inotify: " + std::string(strerror(errno)));
    }
    
    for (const auto& path : config_.watch_paths) {
        int wd = inotify_add_watch(inotify_fd_, path.c_str(),
                                   IN_CREATE | IN_DELETE | IN_MODIFY |
                                   IN_MOVED_FROM | IN_MOVED_TO);
        if (wd < 0) {
            stop();
            return core::Outcome::failure(
                "E_INOTIFY_ADD_WATCH_FAILED",
                "Failed to add watch for " + path + ": " + std::string(strerror(errno)));
        }
        watch_descriptors_.push_back(wd);
    }
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome InotifyAdapter::stop() {
    if (!running_) {
        return core::Outcome::failure("E_NOT_RUNNING", "Adapter not running");
    }
    
    for (int wd : watch_descriptors_) {
        inotify_rm_watch(inotify_fd_, wd);
    }
    watch_descriptors_.clear();
    
    if (inotify_fd_ >= 0) {
        close(inotify_fd_);
        inotify_fd_ = -1;
    }
    
    running_ = false;
    return core::Outcome::success();
}

runtime::Event InotifyAdapter::convert_inotify_event(
    int wd,
    uint32_t mask,
    const std::string& filename) {
    
    std::string event_type;
    if (mask & IN_CREATE) event_type = "file-created";
    else if (mask & IN_DELETE) event_type = "file-deleted";
    else if (mask & IN_MODIFY) event_type = "file-modified";
    else if (mask & IN_MOVED_FROM) event_type = "file-moved-from";
    else if (mask & IN_MOVED_TO) event_type = "file-moved-to";
    else event_type = "filesystem-event";
    
    runtime::Event event;
    event.id = "inotify-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "inotify";
    event.type = event_type;
    
    core::Evidence e1;
    e1.source = "inotify";
    e1.value = std::to_string(wd);
    event.evidence.push_back(e1);
    
    core::Evidence e2;
    e2.source = "inotify";
    e2.value = filename;
    event.evidence.push_back(e2);
    
    core::Evidence e3;
    e3.source = "inotify";
    e3.value = std::to_string(mask);
    event.evidence.push_back(e3);
    
    return event;
}

// ============================================================================
// NativeEventChain Implementation
// ============================================================================

core::Outcome NativeEventChain::create_chain(
    const std::vector<std::string>& watch_paths,
    std::shared_ptr<events::ActivationEngine> engine,
    std::chrono::milliseconds event_timeout_ms) {
    
    if (!engine) {
        return core::Outcome::failure("E_INVALID_ARGUMENT", "ActivationEngine is null");
    }
    
    // In a full implementation, this would:
    // 1. Create adapter instances
    // 2. Register callback with ActivationEngine
    // 3. Start adapters and set up event loop
    
    (void)watch_paths;
    (void)event_timeout_ms;
    
    return core::Outcome::success();
}

size_t NativeEventChain::process_batch(
    std::shared_ptr<events::ActivationEngine> engine,
    std::chrono::milliseconds timeout) {
    
    if (!engine) {
        return 0;
    }
    
    // In a full implementation, this would:
    // 1. Poll all adapter file descriptors with timeout
    // 2. Read and convert events from each adapter
    // 3. Feed to ActivationEngine
    
    (void)timeout;
    return 0;
}

NativeEventChain::Metrics NativeEventChain::get_metrics() {
    Metrics metrics;
    return metrics;
}

}  // namespace rebuntu::adapters