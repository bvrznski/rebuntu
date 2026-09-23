#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::session {
struct SessionSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/session";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::session
