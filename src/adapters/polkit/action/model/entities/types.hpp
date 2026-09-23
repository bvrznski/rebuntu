#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::action::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/action/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::action::model::entities
