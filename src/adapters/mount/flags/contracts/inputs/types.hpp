#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::flags::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/flags/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::flags::contracts::inputs
