// Rebuntu CLI entry point (Phase 0.0)
// =====================================
//
// Phase 0.0: Repository Architecture & Project Skeleton
// This is a structural skeleton, not a functional implementation.
//
// The CLI provides version and components information for verification.

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "rebuntu version 0.0.0\n";
        std::cout << "Repository Architecture & Project Skeleton (Phase 0.0)\n";
        return 0;
    }

    // Handle subcommands
    std::string command = argv[1];

    if (command == "version" || command == "--version" || command == "-v") {
        std::cout << "rebuntu version 0.0.0\n";
        std::cout << "Repository Architecture & Project Skeleton (Phase 0.0)\n";
        return 0;
    }

    if (command == "components" || command == "--components") {
        std::cout << "Rebuntu native foundation components:\n";
        std::cout << "  - rebuntu-native (C++20 core contracts)\n";
        std::cout << "  - CLI entry point\n";
        return 0;
    }

    if (command == "--help" || command == "-h") {
        std::cout << "Usage: rebuntu [COMMAND]\n";
        std::cout << "\nCommands:\n";
        std::cout << "  version, --version, -v   Show version information\n";
        std::cout << "  components                 List available components\n";
        std::cout << "  --help, -h                 Show this help message\n";
        return 0;
    }

    std::cerr << "Unknown command: " << command << "\n";
    std::cerr << "Use 'rebuntu --help' for usage information.\n";
    return 1;
}