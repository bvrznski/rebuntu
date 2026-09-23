#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::subject {
struct SubjectSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/subject";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::subject
