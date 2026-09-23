#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::intent::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/intent/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::intent::model::entities
