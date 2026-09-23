#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::class_node::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/class/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::class_node::contracts::inputs
