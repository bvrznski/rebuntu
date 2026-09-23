#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::event::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/event/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::event::verification::assertions
