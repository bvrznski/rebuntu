#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::request {
struct RequestSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/request";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::request
