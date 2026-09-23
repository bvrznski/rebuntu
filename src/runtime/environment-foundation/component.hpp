#pragma once

#include <filesystem>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::environment_foundation {

enum class Scope { kSystem, kUser };

struct EnvironmentLayout {
    Scope scope{Scope::kUser};
    std::filesystem::path config;
    std::filesystem::path state;
    std::filesystem::path cache;
    std::filesystem::path data;
    std::optional<std::filesystem::path> runtime;
};

struct EnvironmentIssue { std::string code; std::string detail; };
struct EnvironmentAssessment {
    EnvironmentLayout layout;
    std::vector<EnvironmentIssue> issues;
    [[nodiscard]] bool usable() const noexcept { return issues.empty(); }
};

// Computes Rebuntu locations from FHS/XDG semantics. It does not create,
// chown, chmod or otherwise mutate native filesystem state.
class EnvironmentFoundationComponent {
public:
    [[nodiscard]] std::string_view component_name() const noexcept { return "environment-foundation"; }
    [[nodiscard]] EnvironmentAssessment assess_user(const std::filesystem::path& home,
        const std::map<std::string, std::string>& environment) const;
    [[nodiscard]] EnvironmentAssessment assess_system() const;
};

} // namespace rebuntu::runtime::environment_foundation
