#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::audit::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/audit/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::audit::model::entities
