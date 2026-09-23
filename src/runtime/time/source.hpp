// rebuntu::runtime::time::source — Time Source Abstraction (Phase 4.0)
//
// TimeSource provides an abstracted time interface that can be:
// - Injected for testing (with a fixed or controlled clock)
// - Used in production with real system time
//
// This abstraction allows deterministic tests by enabling mock time progression.

#pragma once

#include <runtime/time/error.hpp>
#include <chrono>
#include <thread>
#include <mutex>
#include <memory>

namespace rebuntu::runtime {

class TimeSource {
public:
    virtual ~TimeSource() = default;
    
    // Get current time as system clock (wall clock)
    virtual std::chrono::system_clock::time_point now_system() const = 0;
    
    // Get current steady time (monotonic, for timeouts)
    virtual std::chrono::steady_clock::time_point now_steady() const = 0;
    
    // Convert system time to steady time (for deadline computation)
    virtual std::chrono::steady_clock::time_point to_steady(
        std::chrono::system_clock::time_point sys_time) const = 0;
    
    // Sleep for a duration using the appropriate clock
    virtual void sleep_for(std::chrono::milliseconds duration) const = 0;
};

namespace time {

// Production time source - uses real system clocks
class RealTimeSource : public TimeSource {
public:
    std::chrono::system_clock::time_point now_system() const override {
        return std::chrono::system_clock::now();
    }
    
    std::chrono::steady_clock::time_point now_steady() const override {
        return std::chrono::steady_clock::now();
    }
    
    std::chrono::steady_clock::time_point to_steady(
        std::chrono::system_clock::time_point sys_time) const override {
        // Approximate conversion: difference from epoch
        auto now_sys = std::chrono::system_clock::now();
        auto now_steady = std::chrono::steady_clock::now();
        auto diff = sys_time - now_sys;
        return now_steady + diff;
    }
    
    void sleep_for(std::chrono::milliseconds duration) const override {
        std::this_thread::sleep_for(duration);
    }
};

// Mock time source for testing
class MockTimeSource : public TimeSource {
public:
    explicit MockTimeSource(std::chrono::system_clock::time_point sys_time = 
                           std::chrono::system_clock::now())
        : current_sys_(sys_time), current_steady_(std::chrono::steady_clock::now()) {}
    
    void set_system_time(std::chrono::system_clock::time_point sys_time) {
        std::lock_guard lock(mutex_);
        auto diff = sys_time - current_sys_;
        current_sys_ = sys_time;
        current_steady_ += diff;  // Keep same offset
    }
    
    std::chrono::system_clock::time_point now_system() const override {
        std::lock_guard lock(mutex_);
        return current_sys_;
    }
    
    std::chrono::steady_clock::time_point now_steady() const override {
        std::lock_guard lock(mutex_);
        return current_steady_;
    }
    
    std::chrono::steady_clock::time_point to_steady(
        std::chrono::system_clock::time_point sys_time) const override {
        std::lock_guard lock(mutex_);
        auto diff = sys_time - current_sys_;
        return current_steady_ + diff;
    }
    
    void sleep_for(std::chrono::milliseconds duration) const override {
        // In mock, just advance time (don't actually sleep)
        std::lock_guard lock(mutex_);
        current_sys_ += duration;
        current_steady_ += duration;
    }

private:
    mutable std::mutex mutex_;
    std::chrono::system_clock::time_point current_sys_;
    std::chrono::steady_clock::time_point current_steady_;
};

// Factory function for production time source
inline std::unique_ptr<TimeSource> make_real_time_source() {
    return std::make_unique<RealTimeSource>();
}

// Factory function for mock time source (for testing)
inline std::unique_ptr<TimeSource> make_mock_time_source(
    std::chrono::system_clock::time_point sys_time = std::chrono::system_clock::now()) {
    return std::make_unique<MockTimeSource>(sys_time);
}

}  // namespace time
}  // namespace rebuntu::runtime

// Include the error header after the main implementation
namespace rebuntu { namespace runtime { namespace time {
struct Error {};
}}}