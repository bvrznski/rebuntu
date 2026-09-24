// rebuntu::runtime::SystemdUnitExecutor — Systemd Integration (Phase 0.13)
//
// Implements systemd unit execution using D-Bus to communicate with systemd.

#pragma once

#include <runtime/core/contracts.hpp>
#include <chrono>
#include <string>

namespace rebuntu::runtime {

class SystemdUnitExecutor {
public:
    SystemdUnitExecutor();
    
    // Execute a systemd transient unit
    rebuntu::core::Outcome execute_systemd_unit(
        const std::string& unit_name,
        const std::vector<std::string>& exec_start,
        std::chrono::milliseconds timeout = std::chrono::minutes(5));
};

}  // namespace rebuntu::runtime