// rebuntu::state::ProcfsStateProvider implementation
#include <runtime/state/provider.hpp>
#include <runtime/contracts.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace rebuntu::state {



StateObservation ProcfsStateProvider::observe(const std::string& entity_id) {
    StateObservation obs;
    obs.entity_id = entity_id;
    obs.provider = ProviderId{"procfs"};
    obs.observed_at = std::chrono::system_clock::now();
    
    int64_t pid = -1;
    if (entity_id.find("/proc/") == 0) {
        try {
            pid = std::stoll(entity_id.substr(6));
        } catch (...) {
            obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
            return obs;
        }
    } else {
        try {
            pid = std::stoll(entity_id);
        } catch (...) {
            obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
            return obs;
        }
    }
    
    std::ostringstream proc_path;
    proc_path << "/proc/" << pid << "/stat";
    
    std::ifstream file(proc_path.str());
    if (!file.is_open()) {
        obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
        return obs;
    }
    
    std::string line;
    std::getline(file, line);
    file.close();
    
    if (line.empty()) {
        obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
        return obs;
    }
    
    size_t pos1 = line.find('(');
    size_t pos2 = line.find(')', pos1);
    if (pos1 == std::string::npos || pos2 == std::string::npos) {
        obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
        return obs;
    }
    
    std::istringstream iss(line.substr(pos2 + 2));
    std::string state_str;
    iss >> state_str;
    
    if (state_str.empty()) {
        obs.lifecycle = rebuntu::runtime::LifecycleState::kStopped;
        return obs;
    }
    
    char state_char = state_str[0];
    obs.lifecycle = map_proc_state(state_char);
    obs.work = determine_work_from_proc(state_char, pid);
    
    // Control state: processes are typically enabled (can be controlled)
    obs.control = rebuntu::runtime::ControlState::kEnabled;
    
    // Readiness state: processes that can run are ready
    obs.readiness = rebuntu::runtime::ReadinessState::kReady;
    
    // Health state: healthy unless in zombie/dead state
    if (state_char == 'Z' || state_char == 'X') {
        obs.health = rebuntu::runtime::HealthState::kUnhealthy;
    } else {
        obs.health = rebuntu::runtime::HealthState::kHealthy;
    }
    
    // Recovery state: no recovery in progress for normal processes
    obs.recovery = rebuntu::runtime::RecoveryState::kNone;
    
    obs.native_state_name = std::string(1, state_char);
    obs.pid = pid;
    
    return obs;
}

rebuntu::runtime::LifecycleState ProcfsStateProvider::map_proc_state(char state_char) {
    switch (state_char) {
        case 'R':
            return rebuntu::runtime::LifecycleState::kActive;
        case 'S':
        case 'D':
        case 'W':
            return rebuntu::runtime::LifecycleState::kReady;
        case 'T':
        case 't':
            return rebuntu::runtime::LifecycleState::kStopping;
        case 'Z':
            return rebuntu::runtime::LifecycleState::kStopped;
        case 'X':
            return rebuntu::runtime::LifecycleState::kFailed;
        default:
            return rebuntu::runtime::LifecycleState::kStopped;
    }
}

rebuntu::runtime::WorkState ProcfsStateProvider::determine_work_from_proc(char state_char, int64_t /*pid*/) {
    switch (state_char) {
        case 'R':
            return rebuntu::runtime::WorkState::kProcessing;
        case 'S':
        case 'D':
        case 'W':
            return rebuntu::runtime::WorkState::kWaiting;
        case 'T':
        case 't':
            return rebuntu::runtime::WorkState::kPaused;
        case 'Z':
        case 'X':
            return rebuntu::runtime::WorkState::kIdle;
        default:
            return rebuntu::runtime::WorkState::kIdle;
    }
}

}  // namespace rebuntu::state
