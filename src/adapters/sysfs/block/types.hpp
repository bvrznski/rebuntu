#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::block {
struct BlockSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/block";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::block
