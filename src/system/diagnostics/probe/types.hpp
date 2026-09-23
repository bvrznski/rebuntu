#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::probe {
struct ProbeSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/probe";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::probe
