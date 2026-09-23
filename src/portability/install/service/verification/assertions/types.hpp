#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::service::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/portability/install/service/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::service::verification::assertions
