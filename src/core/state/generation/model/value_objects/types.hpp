#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::generation::model::value_objects {
struct ValueObjectsSkeleton final {
    static constexpr std::string_view path = "src/core/state/generation/model/value_objects";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::generation::model::value_objects
