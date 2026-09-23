#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::goal::model::value_objects {
struct ValueObjectsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/goal/model/value_objects";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::goal::model::value_objects
