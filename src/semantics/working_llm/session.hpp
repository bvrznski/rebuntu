#pragma once
#include <semantics/working_llm/advisory.hpp>
#include <semantics/working_llm/endpoint.hpp>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

namespace rebuntu::semantic::working_llm {

struct PreparedRequest {
    std::string request_id;
    std::string url;
    std::string body;
    RequestBudget budget;
};

class Session {
public:
    explicit Session(Endpoint endpoint = default_bitnet_falcon10b(), RequestBudget budget = {})
        : endpoint_(std::move(endpoint)), budget_(budget) { endpoint_.validate(); budget_.validate(); }

    [[nodiscard]] PreparedRequest prepare(std::string_view operator_text, std::uint64_t sequence) const {
        if (!breaker_.permits()) throw std::runtime_error("working LLM circuit is open");
        if (operator_text.empty() || operator_text.size() > budget_.max_prompt_bytes)
            throw std::invalid_argument("operator prompt violates working LLM budget");
        const auto id = make_request_id(sequence);
        const std::string prompt = guarded_system_prompt() + "\nRequest-ID: " + id + "\nOperator: " + std::string(operator_text);
        return {id, endpoint_.chat_url(), chat_request(prompt, 0.1, budget_.max_tokens), budget_};
    }

    [[nodiscard]] Advisory accept(std::string request_id, std::string content) {
        if (content.empty() || content.size() > budget_.max_response_bytes) {
            breaker_.failure();
            throw std::invalid_argument("working LLM response violates response budget");
        }
        Advisory out;
        out.kind = AdvisoryKind::interpret;
        out.request_id = std::move(request_id);
        out.model = endpoint_.model;
        out.content = std::move(content);
        out.validate();
        breaker_.success();
        return out;
    }

    void transport_failure() noexcept { breaker_.failure(); }
    [[nodiscard]] bool available() const noexcept { return breaker_.permits(); }
    [[nodiscard]] unsigned consecutive_failures() const noexcept { return breaker_.failures(); }

private:
    Endpoint endpoint_;
    RequestBudget budget_;
    mutable CircuitBreaker breaker_{};
};

} // namespace rebuntu::semantic::working_llm
