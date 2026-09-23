#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::pressure::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/pressure/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::pressure::contracts::errors
