// rebuntu::adapters::sysfs_state — Sysfs state provider (Phase 0.16)
//
// Maps sysfs states for devices:
//   power/state: on, suspend
//   uevent: ADD, REMOVE, CHANGE, MOVE

#pragma once

#include <interfaces/state_provider.hpp>
#include <string>

namespace rebuntu::adapters::sysfs_state {

class SysfsStateProvider : public interfaces::StateProvider {
public:
    explicit SysfsStateProvider(std::optional<std::string> sysfs_path = std::nullopt);
    
    ~SysfsStateProvider() override;
    
    interfaces::StateObservation observe(const std::string& entity_id) override;
    
    interfaces::StateProviderId provider_id() const override {
        return interfaces::StateProviderId{"sysfs"};
    }
    
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace rebuntu::adapters::sysfs_state
