#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::report {
struct ReportSkeleton final {
    static constexpr std::string_view path = "src/system/startup/report";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::report
