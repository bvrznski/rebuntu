#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::request::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/request/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::request::model::entities
