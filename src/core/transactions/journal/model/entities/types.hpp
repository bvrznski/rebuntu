#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::journal::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/journal/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::journal::model::entities
