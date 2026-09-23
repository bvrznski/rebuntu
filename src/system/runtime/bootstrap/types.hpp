#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::bootstrap {
struct BootstrapSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/bootstrap";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::bootstrap
