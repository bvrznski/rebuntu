#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::response::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/response/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::response::contracts::errors
