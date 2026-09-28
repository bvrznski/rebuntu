// rebuntu::core::time::monotonic — Integration Utilities (Phase 6.30)
//
// Integration helpers for monotonic deadline propagation through Rebuntu's
// execution system.

#pragma once

#include <runtime/contracts.hpp>
#include <chrono>

namespace rebuntu::core::time {

// -----------------------------------------------------------------------------
// TimeBudgetManager
// -----------------------------------------------------------------------------

class TimeBudgetManager {
public:
    TimeBudgetManager() = default;
    
    explicit TimeBudgetManager(std::chrono::steady_clock::duration total_budget)
        : budget_(total_budget) {}
    
    std::optional<std::chrono::steady_clock::duration> get_remaining() const {
        if (budget_ <= std::chrono::steady_clock::duration{0}) return std::nullopt;
        return budget_;
    }
    
    bool try_consume(std::chrono::steady_clock::duration duration) {
        if (duration > budget_) {
            return false;
        }
        budget_ -= duration;
        return true;
    }
    
private:
    std::chrono::steady_clock::duration budget_{};
};

}  // namespace rebuntu::core::time