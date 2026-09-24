// rebuntu::runtime::SubprocessExecutor — Subprocess Execution (Phase 0.13)
//
// Implements subprocess execution using fork/execve with native Linux primitives.
// This is the canonical subprocess executor for Rebuntu.

#pragma once

#include <runtime/core/contracts.hpp>
#include <string>
#include <vector>
#include <optional>
#include <map>
#include <chrono>

namespace rebuntu::runtime {

class SubprocessExecutor {
public:
    SubprocessExecutor();
    
    // Execute one subprocess with fork/execve
    rebuntu::core::Outcome execute_subprocess(
        const std::string& executable,
        const std::vector<std::string>& argv,
        std::optional<std::string> cwd = std::nullopt,
        std::map<std::string, std::string> env = {},
        std::chrono::milliseconds timeout = std::chrono::minutes(5));
};

}  // namespace rebuntu::runtime