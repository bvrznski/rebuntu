#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::matrix {
struct MatrixSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/matrix";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::matrix
