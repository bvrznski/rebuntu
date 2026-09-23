#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::result {
struct ResultSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/result";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::result
