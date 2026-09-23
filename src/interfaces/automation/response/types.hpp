#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::response {
struct ResponseSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/response";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::response
