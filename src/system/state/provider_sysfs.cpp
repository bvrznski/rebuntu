// rebuntu::state::SysfsStateProvider implementation
#include <system/state/provider.hpp>
#include <runtime/contracts.hpp>

#include <string>
#include <fstream>
#include <sstream>

namespace rebuntu::state {

struct SysfsStateProvider::Impl {
    std::optional<std::string> sysfs_path;
};

SysfsStateProvider::SysfsStateProvider(std::optional<std::string> sysfs_path)
    : impl_(std::make_unique<Impl>()) {
    if (sysfs_path) {
        impl_->sysfs_path = sysfs_path.value();
    } else {
        impl_->sysfs_path = "/sys/class";
    }
}

SysfsStateProvider::~SysfsStateProvider() = default;

StateObservation SysfsStateProvider::observe(const std::string& entity_id) {
    StateObservation obs;
    obs.entity_id = entity_id;
    obs.provider = ProviderId{"sysfs"};
    obs.observed_at = std::chrono::system_clock::now();
    
    if (impl_->sysfs_path) {
        std::ostringstream path;
        path << impl_->sysfs_path.value() << "/" << entity_id << "/uevent";
        
        std::ifstream file(path.str());
        if (!file.is_open()) {
            obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
            return obs;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("ADD") != std::string::npos) {
                obs.lifecycle = rebuntu::runtime::LifecycleState::kActive;
                break;
            } else if (line.find("REMOVE") != std::string::npos) {
                obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
                break;
            }
        }
        
        if (obs.lifecycle == rebuntu::runtime::LifecycleState::kStopped) {
            std::ostringstream power_path;
            power_path << impl_->sysfs_path.value() << "/" << entity_id << "/power/state";
            
            std::ifstream power_file(power_path.str());
            if (power_file.is_open()) {
                std::string state;
                power_file >> state;
                if (state == "on") {
                    obs.lifecycle = rebuntu::runtime::LifecycleState::kActive;
                } else if (state == "suspend" || state == "off") {
                    obs.lifecycle = rebuntu::runtime::LifecycleState::kReady;
                }
            } else {
                obs.lifecycle = rebuntu::runtime::LifecycleState::kReady;
            }
        }
    } else {
        obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
    }
    
    return obs;
}

}  // namespace rebuntu::state
