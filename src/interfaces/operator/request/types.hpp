#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::request {
struct RequestSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/request";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::request
