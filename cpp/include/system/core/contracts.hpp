// Rebuntu Core Contracts (Phase 0.0)
// ====================================

#pragma once

#include <string>
#include <chrono>
#include <memory>
#include <map>
#include <optional>

namespace rebuntu::work {

struct ExecutionId {
    std::string value;
    ExecutionId() = default;
    explicit ExecutionId(std::string v) : value(std::move(v)) {}
};

enum class WorkPriority : uint8_t {
    kBackground = 0,
    kNormal = 1,
    kHigh = 2,
    kCritical = 3
};

} // namespace rebuntu::work

namespace rebuntu::core {

struct TimeoutPolicy {
    std::chrono::milliseconds default_timeout = std::chrono::minutes(5);
    std::chrono::milliseconds verification_timeout = std::chrono::seconds(30);
    bool cancel_on_timeout = true;
};

struct RetryPolicy {
    uint32_t max_attempts = 1;
    std::chrono::milliseconds initial_backoff = std::chrono::milliseconds(100);
    std::chrono::milliseconds max_backoff = std::chrono::seconds(5);
    bool use_exponential_backoff = true;
};

} // namespace rebuntu::core

namespace rebuntu::runtime {

class EvidenceRegistry;

struct CancellationToken {
    bool is_cancelled() const { return cancelled; }
    void request_cancel(std::string = "") { cancelled = true; }
private:
    bool cancelled = false;
};

struct RuntimeContext {
    work::ExecutionId execution_id;
    std::string caller_id;
    std::chrono::system_clock::time_point created_at;
    core::TimeoutPolicy timeout_policy;
    core::RetryPolicy retry_policy;
    std::shared_ptr<CancellationToken> cancellation_token;
    std::optional<std::string> working_directory;
    std::map<std::string, std::string> environment;
    std::shared_ptr<EvidenceRegistry> evidence_registry;
    work::WorkPriority priority = work::WorkPriority::kNormal;
    bool allow_concurrent_execution = true;
};

} // namespace rebuntu::runtime