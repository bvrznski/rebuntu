#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::report {
struct ReportSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/report";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::report
