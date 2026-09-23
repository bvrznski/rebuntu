#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::deprecation::notice {
struct NoticeSkeleton final {
    static constexpr std::string_view path = "src/governance/deprecation/notice";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::deprecation::notice
