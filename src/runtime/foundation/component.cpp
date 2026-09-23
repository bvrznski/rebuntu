#include "component.hpp"

#include <algorithm>
#include <system_error>

namespace rebuntu::runtime::foundation {

bool ArchitectureAudit::satisfied() const noexcept {
    return std::all_of(findings.begin(), findings.end(), [](const auto& f) {
        return f.state == RequirementState::kSatisfied;
    });
}

std::size_t ArchitectureAudit::missing_count() const noexcept {
    return static_cast<std::size_t>(std::count_if(findings.begin(), findings.end(), [](const auto& f) {
        return f.state != RequirementState::kSatisfied;
    }));
}

std::vector<StructuralRequirement> FoundationComponent::canonical_requirements() const {
    return {
        {"src/runtime", true, "execution lifecycle and runtime mechanics"},
        {"src/semantics", true, "Rebuntu semantic model"},
        {"src/observation", true, "native-state observation and evidence acquisition"},
        {"src/knowledge", true, "derived knowledge, history and topology"},
        {"src/planning", true, "goal decomposition and plan synthesis"},
        {"src/control", true, "verification, reconciliation and recovery"},
        {"src/security", true, "policy, authorization and trust semantics"},
        {"src/domains", true, "domain semantics without Linux-mechanism duplication"},
        {"src/automation", true, "workflow and trigger orchestration"},
        {"src/operator", true, "operator-facing commands and explanations"},
        {"src/providers/linux", true, "narrow typed boundaries to native Linux authorities"},
        {"tests", true, "verification and regression tests"},
        {".phases/AGENTS.md", false, "phase implementation contract"},
        {".phases/phases", true, "source phase specifications and living ledgers"},
    };
}

ArchitectureAudit FoundationComponent::audit(const std::filesystem::path& repository_root) const {
    ArchitectureAudit result;
    for (const auto& requirement : canonical_requirements()) {
        const auto path = repository_root / requirement.relative_path;
        std::error_code ec;
        const auto status = std::filesystem::status(path, ec);
        RequirementState state = RequirementState::kMissing;
        if (!ec && std::filesystem::exists(status)) {
            const bool type_ok = requirement.directory ? std::filesystem::is_directory(status)
                                                       : std::filesystem::is_regular_file(status);
            state = type_ok ? RequirementState::kSatisfied : RequirementState::kWrongType;
        }
        result.findings.push_back({requirement, state});
    }
    return result;
}

std::string_view to_string(RequirementState state) noexcept {
    switch (state) {
        case RequirementState::kSatisfied: return "satisfied";
        case RequirementState::kMissing: return "missing";
        case RequirementState::kWrongType: return "wrong_type";
    }
    return "missing";
}

} // namespace rebuntu::runtime::foundation
