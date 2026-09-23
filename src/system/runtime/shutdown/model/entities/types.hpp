#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::shutdown::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/shutdown/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::shutdown::model::entities
