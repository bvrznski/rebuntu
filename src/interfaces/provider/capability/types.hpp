#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::capability {
struct CapabilitySkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/capability";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::capability
