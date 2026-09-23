#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::rollback {
struct RollbackSkeleton final {
    static constexpr std::string_view path = "src/system/startup/rollback";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::rollback
