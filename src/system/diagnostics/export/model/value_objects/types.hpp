#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::export_node::model::value_objects {
struct ValueObjectsSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/export/model/value_objects";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::export_node::model::value_objects
