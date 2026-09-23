#pragma once
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantic::working_llm {

enum class AdvisoryKind { interpret, explain, propose };

struct Advisory {
    AdvisoryKind kind{AdvisoryKind::interpret};
    std::string request_id;
    std::string model;
    std::string content;
    std::vector<std::string> assumptions;
    bool authoritative{false};
    bool requests_native_execution{false};

    void validate() const {
        if (request_id.empty() || model.empty() || content.empty())
            throw std::invalid_argument("LLM advisory requires request/model/content provenance");
        if (authoritative) throw std::invalid_argument("LLM advisory cannot be authoritative");
        if (requests_native_execution)
            throw std::invalid_argument("LLM advisory cannot request direct native execution");
        if (content.size() > 64U * 1024U) throw std::invalid_argument("LLM advisory exceeds semantic budget");
    }
};

struct RequestBudget {
    unsigned max_prompt_bytes{32U * 1024U};
    unsigned max_response_bytes{64U * 1024U};
    unsigned max_tokens{1024};
    std::chrono::milliseconds timeout{30000};
    unsigned max_attempts{2};

    void validate() const {
        if (!max_prompt_bytes || !max_response_bytes || !max_tokens || !timeout.count() || !max_attempts)
            throw std::invalid_argument("working LLM budgets must be non-zero");
        if (max_attempts > 3) throw std::invalid_argument("working LLM retry budget is intentionally bounded");
    }
};

class CircuitBreaker {
public:
    explicit CircuitBreaker(unsigned threshold = 3) : threshold_(threshold) {
        if (!threshold_) throw std::invalid_argument("circuit breaker threshold must be non-zero");
    }
    [[nodiscard]] bool permits() const noexcept { return failures_ < threshold_; }
    void success() noexcept { failures_ = 0; }
    void failure() noexcept { if (failures_ < threshold_) ++failures_; }
    [[nodiscard]] unsigned failures() const noexcept { return failures_; }
private:
    unsigned threshold_;
    unsigned failures_{0};
};

inline std::string guarded_system_prompt() {
    return "You are Rebuntu's non-authoritative working LLM. Interpret and explain only. "
           "Never claim to have observed Linux state, never claim an operation succeeded, and never bypass "
           "typed semantics, policy, planning, control, verification, or native Linux providers. "
           "Return proposals for deterministic validation; do not emit shell commands as executed actions.";
}

inline std::string make_request_id(std::uint64_t sequence) {
    if (!sequence) throw std::invalid_argument("LLM request sequence must be non-zero");
    return "working-llm-" + std::to_string(sequence);
}

} // namespace rebuntu::semantic::working_llm
