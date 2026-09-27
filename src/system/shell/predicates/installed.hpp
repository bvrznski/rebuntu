// rebuntu::shell::predicates::installed — Installed Predicate (Phase 6.0)
//
// This module implements the "installed" predicate:
//   - Returns TRUE if a package is installed
//   - Returns FALSE if a package is not installed  
//   - Returns UNKNOWN if state cannot be determined

#pragma once

#include "../types.hpp"
#include <adapters/package_managers/dpkg/types.hpp>
#include <string>

namespace rebuntu::shell::predicates {

// ============================================================================
// installed_predicate — Check if a package is installed
//
// This predicate queries the dpkg database to determine if a package exists.
// The result carries three-valued logic: TRUE/FALSE/UNKNOWN.
// ============================================================================

PredicateResult installed_predicate(const std::string& package_name);

}  // namespace rebuntu::shell::predicates