#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::error::model::value_objects {
struct ValueObjectsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/error/model/value_objects";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::error::model::value_objects
