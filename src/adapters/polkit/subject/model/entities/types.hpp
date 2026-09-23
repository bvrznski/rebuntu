#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::subject::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/subject/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::subject::model::entities
