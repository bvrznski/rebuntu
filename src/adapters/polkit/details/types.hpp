#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::details {
struct DetailsSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/details";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::details
