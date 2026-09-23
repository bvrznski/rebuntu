#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::event {
struct EventSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/event";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::event
