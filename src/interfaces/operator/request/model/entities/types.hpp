#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::operator_node::request::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/operator/request/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::operator_node::request::model::entities
