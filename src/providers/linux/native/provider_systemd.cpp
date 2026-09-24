// rebuntu::state::SystemdStateProvider implementation
#include <runtime/state/provider.hpp>
#include <runtime/contracts.hpp>

namespace rebuntu::state {

struct SystemdStateProvider::Impl {
    static constexpr std::string_view DBUS_SERVICE = "org.freedesktop.systemd1";
};

SystemdStateProvider::SystemdStateProvider(std::optional<std::string> /*dbus_address*/) {}

SystemdStateProvider::~SystemdStateProvider() = default;

StateObservation SystemdStateProvider::observe(const std::string& entity_id) {
    StateObservation obs;
    obs.entity_id = entity_id;
    obs.provider = ProviderId{"systemd"};
    obs.observed_at = std::chrono::system_clock::now();
    
    // Default: systemd unit is enabled and ready for activation
    obs.lifecycle = rebuntu::runtime::LifecycleState::kReady;
    obs.control = rebuntu::runtime::ControlState::kEnabled;
    obs.readiness = rebuntu::runtime::ReadinessState::kNotReady;  // Not yet ready until activated
    obs.health = rebuntu::runtime::HealthState::kHealthy;
    obs.recovery = rebuntu::runtime::RecoveryState::kNone;
    
    return obs;
}

rebuntu::runtime::LifecycleState SystemdStateProvider::map_active_state(std::string_view active, std::string_view sub) {
    if (active == "active" || sub == "running") {
        return rebuntu::runtime::LifecycleState::kActive;
    } else if (active == "activating") {
        return rebuntu::runtime::LifecycleState::kInitializing;
    } else if (active == "deactivating") {
        return rebuntu::runtime::LifecycleState::kStopping;
    } else if (active == "failed") {
        return rebuntu::runtime::LifecycleState::kFailed;
    } else if (active == "inactive" || active == "not-found") {
        return rebuntu::runtime::LifecycleState::kReady;
    }
    return rebuntu::runtime::LifecycleState::kStopped;
}

rebuntu::runtime::HealthState SystemdStateProvider::determine_health_from_systemd(std::string_view /*unit_file_state*/) {
    return rebuntu::runtime::HealthState::kHealthy;
}

}  // namespace rebuntu::state
