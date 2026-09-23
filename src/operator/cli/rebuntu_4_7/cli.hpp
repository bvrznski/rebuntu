// rebuntu::cli — the Rebuntu command-line surface (Phase 0.0)
//
// `bin/rebuntu` is a thin shell wrapper that dispatches into this native
// implementation. The CLI is a PRESENTATION SURFACE: it expresses typed
// intent and reports structured results. It must never become an
// independent system controller (see docs/ARCHITECTURE.md §11 and
// AGENTS.md §31).
#pragma once

#include <span>

namespace rebuntu::cli {

// Dispatch the Rebuntu CLI.
// Returns a process exit code: 0 on success, 1 on usage/semantic failure.
// `argv` is the full argument vector, argv[0] being the program name.
int run(std::span<const char* const> argv);

}  // namespace rebuntu::cli
