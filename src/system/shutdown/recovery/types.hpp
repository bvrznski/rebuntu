#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::recovery {
struct RecoverySkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/recovery";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::recovery
