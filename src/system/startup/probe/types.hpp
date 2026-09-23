#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::probe {
struct ProbeSkeleton final {
    static constexpr std::string_view path = "src/system/startup/probe";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::probe
