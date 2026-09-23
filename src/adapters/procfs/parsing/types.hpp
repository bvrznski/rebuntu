#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::parsing {
struct ParsingSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/parsing";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::parsing
