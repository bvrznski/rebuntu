#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::request {
struct RequestSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/request";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::request
