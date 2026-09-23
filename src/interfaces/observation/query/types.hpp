#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::query {
struct QuerySkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/query";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::query
