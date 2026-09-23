#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::service {
struct ServiceSkeleton final {
    static constexpr std::string_view path = "src/portability/install/service";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::service
