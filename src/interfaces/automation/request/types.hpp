#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::request {
struct RequestSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/request";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::request
