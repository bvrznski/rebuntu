#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::signals::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/signals/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::signals::contracts::inputs
