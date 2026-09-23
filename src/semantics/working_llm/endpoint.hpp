#pragma once
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>

namespace rebuntu::semantic::working_llm {

struct Endpoint {
    std::string provider{"bitnet.cpp"};
    std::string model{"Falcon3-10B-Instruct-1.58bit"};
    std::string base_url{"http://127.0.0.1:8082"};
    std::string chat_path{"/v1/chat/completions"};
    unsigned context_tokens{4096};
    bool local_only{true};
    bool authoritative{false};

    [[nodiscard]] std::string chat_url() const { return base_url + chat_path; }

    void validate() const {
        if (provider.empty() || model.empty()) throw std::invalid_argument("working LLM identity must be explicit");
        if (chat_path.empty() || chat_path.front() != '/') throw std::invalid_argument("working LLM chat path must be absolute");
        if (context_tokens == 0) throw std::invalid_argument("working LLM context must be non-zero");
        if (authoritative) throw std::invalid_argument("LLM output may not be an authority in Rebuntu");
        if (local_only && base_url != "http://127.0.0.1:8082" && base_url != "http://localhost:8082")
            throw std::invalid_argument("local-only working LLM must bind to loopback");
    }
};

inline Endpoint default_bitnet_falcon10b() {
    Endpoint e;
    e.validate();
    return e;
}

inline std::string json_escape(std::string_view input) {
    std::string out;
    out.reserve(input.size() + 16);
    for (unsigned char c : input) {
        switch (c) {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c < 0x20) throw std::invalid_argument("control character not allowed in LLM prompt");
                out.push_back(static_cast<char>(c));
        }
    }
    return out;
}

inline std::string chat_request(std::string_view prompt, double temperature = 0.1, unsigned max_tokens = 512) {
    if (prompt.empty()) throw std::invalid_argument("working LLM prompt must not be empty");
    if (temperature < 0.0 || temperature > 2.0) throw std::invalid_argument("temperature out of range");
    if (max_tokens == 0 || max_tokens > 4096) throw std::invalid_argument("max_tokens out of range");
    return "{\"messages\":[{\"role\":\"user\",\"content\":\"" + json_escape(prompt) +
           "\"}],\"temperature\":" + std::to_string(temperature) +
           ",\"max_tokens\":" + std::to_string(max_tokens) + "}";
}

} // namespace rebuntu::semantic::working_llm
