#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::translation {
struct TranslationSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/translation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::translation
