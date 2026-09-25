// rebuntu::runtime::TimeoutEnforcement — Kernel-Enforced Timeout (Phase 0.13)
//
// Implements timeout enforcement using timerfd for native Linux kernel timeouts.
// This is the authoritative timeout mechanism for Rebuntu execution runtime.

#pragma once

#include <system/core/contracts.hpp>
#include <chrono>
#include <string>

namespace rebuntu::runtime {

class TimeoutEnforcement {
public:
    TimeoutEnforcement();
    
    // Create a timerfd for timeout enforcement
    int create_timerfd(std::chrono::milliseconds duration);
    
    // Wait for timeout with cancellation support
    bool wait_for_timeout(int timer_fd, std::chrono::milliseconds remaining);
    
    // Cancel an active timeout
    void cancel_timeout(int timer_fd);
};

}  // namespace rebuntu::runtime