#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::export_node::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/export/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::export_node::model::entities
