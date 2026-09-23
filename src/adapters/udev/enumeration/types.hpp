#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::enumeration {
struct EnumerationSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/enumeration";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::enumeration
