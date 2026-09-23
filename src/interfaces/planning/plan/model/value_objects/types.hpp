#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::plan::model::value_objects {
struct ValueObjectsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/plan/model/value_objects";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::plan::model::value_objects
