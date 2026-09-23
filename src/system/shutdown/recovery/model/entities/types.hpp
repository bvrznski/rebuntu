#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::recovery::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/recovery/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::recovery::model::entities
