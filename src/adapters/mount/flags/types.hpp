#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::flags {
struct FlagsSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/flags";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::flags
