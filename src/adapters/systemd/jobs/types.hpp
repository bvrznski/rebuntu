#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::jobs {
struct JobsSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/jobs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::jobs
