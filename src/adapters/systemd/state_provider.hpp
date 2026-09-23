// rebuntu::adapters::systemd_state — systemd state provider (Phase 0.16)
//
// Maps systemd ActiveState/SubState/UnitFileState to Rebuntu state:
//   ActiveState: active, inactive, activating, deactivating, failed, not-found
//   SubState: various (e.g., running, dead, mounted)

#pragma once

#include <interfaces/state_provider.hpp>
#include <string>
#include <optional>

namespace rebuntu::adapters::systemd_state {

class SystemdStateProvider : public interfaces::StateProvider {
public:
    explicit SystemdStateProvider(std::optional<std::string> dbus_address = std::nullopt);
    
    ~SystemdStateProvider() override;
    
    interfaces::StateObservation observe(const std::string& entity_id) override;
    
    interfaces::StateProviderId provider_id() const override {
        return interfaces::StateProviderId{"systemd"};
    }
    
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    
    rebuntu::runtime::LifecycleState map_active_state(std::string_view active, std::string_view sub);
    rebuntu::runtime::HealthState determine_health_from_systemd(std::string_view unit_file_state);
};

}  // namespace rebuntu::adapters::systemd_state
