#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::transaction::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/transaction/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::transaction::model::entities
