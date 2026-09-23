#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::policy::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/shell/policy/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::policy::model::entities
