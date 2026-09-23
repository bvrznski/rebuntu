#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::history {
struct HistorySkeleton final {
    static constexpr std::string_view path = "src/system/state/history";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::history
