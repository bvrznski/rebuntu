#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::table {
struct TableSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/table";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::table
