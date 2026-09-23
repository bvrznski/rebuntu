#pragma once

#include <string_view>

namespace rebuntu::runtime::system_state_and_events {

// Structural integration point for system state and events.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemStateAndEventsComponent {
public:
    virtual ~SystemStateAndEventsComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-state-and-events"; }
};

} // namespace rebuntu::runtime::system_state_and_events
