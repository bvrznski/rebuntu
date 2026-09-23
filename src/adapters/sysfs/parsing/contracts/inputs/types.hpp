#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::parsing::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/parsing/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::parsing::contracts::inputs
