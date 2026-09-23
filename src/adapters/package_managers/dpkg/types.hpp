#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::package_managers::dpkg {
struct DpkgSkeleton final {
    static constexpr std::string_view path = "src/adapters/package_managers/dpkg";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::package_managers::dpkg
