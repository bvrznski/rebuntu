#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::session::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/session/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::session::contracts::errors
