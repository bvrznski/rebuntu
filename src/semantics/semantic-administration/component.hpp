#pragma once

#include <string_view>

namespace rebuntu::semantics::semantic_administration {

// Structural integration point for semantic administration.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SemanticAdministrationComponent {
public:
    virtual ~SemanticAdministrationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "semantic-administration"; }
};

} // namespace rebuntu::semantics::semantic_administration
