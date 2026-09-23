#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::error_mapping::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/error_mapping/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::error_mapping::verification::assertions
