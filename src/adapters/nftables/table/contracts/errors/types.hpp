#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::table::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/table/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::table::contracts::errors
