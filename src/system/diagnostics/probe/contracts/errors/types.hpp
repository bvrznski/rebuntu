#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::probe::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/probe/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::probe::contracts::errors
