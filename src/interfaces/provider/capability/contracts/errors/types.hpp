#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::capability::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/capability/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::capability::contracts::errors
