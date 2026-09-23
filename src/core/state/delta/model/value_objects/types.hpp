#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::delta::model::value_objects {
struct ValueObjectsSkeleton final {
    static constexpr std::string_view path = "src/core/state/delta/model/value_objects";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::delta::model::value_objects
