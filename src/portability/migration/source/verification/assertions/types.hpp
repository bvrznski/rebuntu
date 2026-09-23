#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::source::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/source/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::source::verification::assertions
