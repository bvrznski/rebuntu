#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::discovery::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/discovery/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::discovery::contracts::errors
