#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::exception {
struct ExceptionSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/exception";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::exception
