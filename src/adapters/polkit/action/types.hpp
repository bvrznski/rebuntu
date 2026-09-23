#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::action {
struct ActionSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/action";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::action
