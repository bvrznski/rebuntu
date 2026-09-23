// rebuntu::adapters::procfs_state — Procfs state provider (Phase 0.16)
//
// Maps Linux process states from /proc/[pid]/stat to Rebuntu state:
//   R = running, S = sleeping, D = disk sleep, T = stopped
//   Z = zombie, X = dead, t = tracing stop, W = paging

#pragma once

#include <interfaces/state_provider.hpp>
#include <string>

namespace rebuntu::adapters::procfs_state {

class ProcfsStateProvider : public interfaces::StateProvider {
public:
    ProcfsStateProvider() = default;
    ~ProcfsStateProvider() override = default;
    
    interfaces::StateObservation observe(const std::string& entity_id) override;
    
    interfaces::StateProviderId provider_id() const override {
        return interfaces::StateProviderId{"procfs"};
    }
    
private:
    rebuntu::runtime::LifecycleState map_proc_state(char state_char);
    rebuntu::runtime::WorkState determine_work_from_proc(char state_char, int64_t pid);
};

}  // namespace rebuntu::adapters::procfs_state
