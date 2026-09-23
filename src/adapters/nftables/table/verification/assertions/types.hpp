#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::table::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/table/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::table::verification::assertions
