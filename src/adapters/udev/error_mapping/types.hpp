#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::error_mapping {
struct ErrorMappingSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/error_mapping";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::error_mapping
