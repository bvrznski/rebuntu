#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::package_managers::flatpak {
struct FlatpakSkeleton final {
    static constexpr std::string_view path = "src/adapters/package_managers/flatpak";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::package_managers::flatpak
