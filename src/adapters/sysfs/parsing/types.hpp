#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::parsing {
struct ParsingSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/parsing";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::parsing
