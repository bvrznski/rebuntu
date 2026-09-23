#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::checkpoint {
struct CheckpointSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/checkpoint";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::checkpoint
