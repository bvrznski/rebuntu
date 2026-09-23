#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::result::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/result/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::result::model::entities
