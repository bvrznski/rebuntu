#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::subscription {
struct SubscriptionSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/subscription";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::subscription
