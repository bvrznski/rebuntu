#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::deprecation::migration_path::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/governance/deprecation/migration_path/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::deprecation::migration_path::contracts::errors
