#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::result {
struct ResultSkeleton final {
    static constexpr std::string_view path = "src/system/shell/result";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::result
