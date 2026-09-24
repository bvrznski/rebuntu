// rebuntu::runtime::TimeoutEnforcement — Kernel-Enforced Timeout (Phase 0.13)
//
// Implements timeout enforcement using timerfd for native Linux kernel timeouts.
// This is the authoritative timeout mechanism for Rebuntu execution runtime.

#include <runtime/timeout_enforcement.hpp>
#include <sys/timerfd.h>
#include <unistd.h>

namespace rebuntu::runtime {

TimeoutEnforcement::TimeoutEnforcement() = default;

int TimeoutEnforcement::create_timerfd(std::chrono::milliseconds duration) {
    // Create a timerfd using native Linux kernel interface
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
    
    if (timer_fd == -1) {
        return -1;
    }
    
    // Set up the timer specification
    itimerspec timer_spec{};
    timer_spec.it_value.tv_sec = duration.count() / 1000;
    timer_spec.it_value.tv_nsec = (duration.count() % 1000) * 1000000;
    
    // Arm the timer
    if (timerfd_settime(timer_fd, 0, &timer_spec, nullptr) == -1) {
        close(timer_fd);
        return -1;
    }
    
    return timer_fd;
}

bool TimeoutEnforcement::wait_for_timeout(int timer_fd, std::chrono::milliseconds remaining) {
    (void)remaining;  // Not used in this minimal implementation
    
    if (timer_fd < 0) {
        return false;
    }
    
    uint64_t expirations = 0;
    ssize_t bytes_read = read(timer_fd, &expirations, sizeof(expirations));
    
    close(timer_fd);
    
    // If we read data, timer expired
    return bytes_read > 0 && expirations > 0;
}

void TimeoutEnforcement::cancel_timeout(int timer_fd) {
    if (timer_fd >= 0) {
        itimerspec disarm_spec{};
        timerfd_settime(timer_fd, 0, &disarm_spec, nullptr);
        close(timer_fd);
    }
}

}  // namespace rebuntu::runtime