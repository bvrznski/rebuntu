#pragma once

#include <string_view>

namespace rebuntu::runtime::unified_search_command_system {

// Structural integration point for unified search command system.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class UnifiedSearchCommandSystemComponent {
public:
    virtual ~UnifiedSearchCommandSystemComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "unified-search-command-system"; }
};

} // namespace rebuntu::runtime::unified_search_command_system
