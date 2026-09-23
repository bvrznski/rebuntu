#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::schema::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/schema/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::schema::contracts::errors
