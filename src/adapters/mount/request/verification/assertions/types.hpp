#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::request::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/request/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::request::verification::assertions
