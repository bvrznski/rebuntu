#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::session::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/session/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::session::model::entities
