// rebuntu::shell::verbs::list — List Command (Phase 6.0)
//
// This module implements the "list" mutating verb:
//   - list services [--scope system|user]
//   - list packages [--installed|--available]

#pragma once

#include "../types.hpp"

namespace rebuntu::shell::verbs {

CommandResult list_command(const CommandIntent& intent);

}  // namespace rebuntu::shell::verbs