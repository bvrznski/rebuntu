#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::foundation {

enum class RequirementState { kSatisfied, kMissing, kWrongType };

struct StructuralRequirement {
    std::filesystem::path relative_path;
    bool directory{true};
    std::string responsibility;
};

struct StructuralFinding {
    StructuralRequirement requirement;
    RequirementState state{RequirementState::kMissing};
};

struct ArchitectureAudit {
    std::vector<StructuralFinding> findings;
    [[nodiscard]] bool satisfied() const noexcept;
    [[nodiscard]] std::size_t missing_count() const noexcept;
};

// Phase-0 architecture contract checker. It verifies Rebuntu-owned repository
// structure only; it never attempts to reproduce or replace Linux facilities.
class FoundationComponent {
public:
    [[nodiscard]] std::string_view component_name() const noexcept { return "foundation"; }
    [[nodiscard]] std::vector<StructuralRequirement> canonical_requirements() const;
    [[nodiscard]] ArchitectureAudit audit(const std::filesystem::path& repository_root) const;
};

[[nodiscard]] std::string_view to_string(RequirementState state) noexcept;

} // namespace rebuntu::runtime::foundation
