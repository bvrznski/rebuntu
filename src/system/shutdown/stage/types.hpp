#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::stage {
struct StageSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/stage";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::stage
