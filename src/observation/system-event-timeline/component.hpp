#pragma once

#include <string_view>

namespace rebuntu::observation::system_event_timeline {

// Structural integration point for system event timeline.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemEventTimelineComponent {
public:
    virtual ~SystemEventTimelineComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-event-timeline"; }
};

} // namespace rebuntu::observation::system_event_timeline
