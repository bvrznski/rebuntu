#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::notification {
struct NotificationSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/notification";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::notification
