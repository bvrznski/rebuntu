#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::failure {
struct FailureSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/failure";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::failure
