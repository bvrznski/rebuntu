#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::context {
struct ContextSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/context";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::context
