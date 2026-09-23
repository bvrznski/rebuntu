#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace rebuntu::runtime::preflight {

enum class SupportLevel { supported, tested, unknown, unsupported };
enum class Severity { info, warning, blocker };

struct Fact {
    std::string key;
    std::string value;
    std::string source;
    bool known{false};
};

struct Finding {
    Severity severity{Severity::info};
    std::string requirement;
    std::string message;
};

struct Report {
    std::map<std::string, Fact> facts;
    std::vector<Finding> findings;
    SupportLevel support{SupportLevel::unknown};
    bool ready() const;
    std::string human_summary() const;
};

struct Policy {
    std::vector<std::string> tested_distributions{"ubuntu", "debian"};
    std::vector<std::string> supported_architectures{"x86_64", "aarch64"};
    std::uintmax_t minimum_free_bytes{512ULL * 1024ULL * 1024ULL};
    bool require_systemd{true};
};

class HostPreflight {
public:
    Report inspect(const Policy& policy = {}) const;
    static Report evaluate(std::map<std::string, Fact> facts, const Policy& policy = {});
};

} // namespace rebuntu::runtime::preflight
