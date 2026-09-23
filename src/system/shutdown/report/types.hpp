#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::report {
struct ReportSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/report";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::report
