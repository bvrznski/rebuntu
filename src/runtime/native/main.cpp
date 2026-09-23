// `rebuntu` — primary user-facing entry point (Phase 0.0).
// Thin by design: it dispatches into the native CLI implementation.
#include "cli.hpp"

#include <span>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::vector<const char*> args(argv, argv + argc);
    if (args.empty()) {
        return 1;
    }
    // args[0] is the program name. We dispatch on args[1..] so that both
    // `rebuntu version` and `rebuntu --version` work, and a bare `rebuntu`
    // prints help.
    std::span<const char* const> dispatch(args.begin() + 1, args.end());
    return rebuntu::cli::run(dispatch);
}
