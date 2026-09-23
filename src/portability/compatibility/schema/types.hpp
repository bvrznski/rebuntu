#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::schema {
struct SchemaSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/schema";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::schema
