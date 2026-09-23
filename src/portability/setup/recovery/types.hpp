#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::recovery {
struct RecoverySkeleton final {
    static constexpr std::string_view path = "src/portability/setup/recovery";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::recovery
