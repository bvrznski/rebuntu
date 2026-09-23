// rebuntu::core — project version (Phase 0.0)
#pragma once

#include <string_view>

namespace rebuntu::core {

// Single source of truth for the project version, surfaced by
// `rebuntu --version` and the `rebuntu` CLI. Bump deliberately.
inline constexpr std::string_view kVersion = "0.0.0";

// A coarse lifecycle stage for human-readable status reports.
// Kept intentionally small; the full phase taxonomy lives in docs/ROADMAP.md
// and the historical corpus under .phases/.
inline constexpr std::string_view kPhase = "0.0";

// The structural root namespace of the primary implementation package.
// Rebuntu's primary package is `system` (see docs/ARCHITECTURE.md).
inline constexpr std::string_view kPackageName = "system";

}  // namespace rebuntu::core
