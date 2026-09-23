#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::failure {
struct FailureSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/failure";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::failure
