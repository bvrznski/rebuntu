#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::report {
struct ReportSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/report";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::report
