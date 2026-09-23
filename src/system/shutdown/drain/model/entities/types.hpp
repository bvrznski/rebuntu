#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::drain::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/drain/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::drain::model::entities
