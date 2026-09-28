// rebuntu::cli — Native CLI Entry Point (Phase 5.60)
//
// This module provides the main entry point for the Rebuntu native CLI:
//   - Parses command-line arguments at the interface edge
//   - Converts to typed CommandIntent via parser boundary (Task 6.46)
//   - Dispatches to appropriate commands using typed intent
//   - Outputs results with freshness and source information
//
// Parser Boundary (Task 6.46):
//   CLI text input → tokenize/parse_argv → typed CommandIntent → dispatch
//   Domain code receives ONLY typed structures, NO string re-parsing.

#include <iostream>
#include <string>
#include <vector>

#include "inventory/types.hpp"
#include "inventory/query.hpp"

#include "parser.hpp"  // Task 6.46 parser boundary

#include <system/observation/output/types.hpp>
#include <system/shell/collision_scanner.hpp>

namespace rebuntu::cli {

void print_usage(const std::string& program) {
    std::cout << "rebuntu — Native system inspection CLI (Phase 5.60)\n\n";
    std::cout << "Usage: " << program << " inventory <kind> [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  inventory packages [OPTIONS]   List all installed packages\n\n";
    std::cout << "Options:\n";
    std::cout << "  --format <json|table>     Output format (default: table)\n";
    std::cout << "  --freshness <seconds>     Freshness threshold in seconds (default: 300)\n";
    std::cout << "  --max <count>             Maximum number of results to show\n";
    std::cout << "  --verbose                 Show full freshness and source information\n";
    std::cout << "\n";
}

void print_package_header() {
    std::cout << "NAME                  VERSION              STATE           SOURCE      FRESHNESS\n";
    std::cout << "-----------------------------------------------------------------------------------\n";
}

std::string format_freshness(const inventory::FreshnessReport& freshness) {
    if (freshness.source_kind == inventory::FreshnessReport::Source::kUnknown) {
        return "unknown";
    }
    
    if (freshness.is_stale) {
        return "STALE";
    }
    
    auto age_seconds = std::chrono::duration_cast<std::chrono::seconds>(freshness.age_ms).count();
    if (age_seconds < 60) {
        return std::to_string(age_seconds) + "s";
    } else if (age_seconds < 3600) {
        return std::to_string(age_seconds / 60) + "m";
    } else {
        return std::to_string(age_seconds / 3600) + "h";
    }
}

void print_package(const inventory::EntityInfo& pkg, bool verbose = false) {
    // Package name (first 19 chars)
    std::string name = pkg.name.value_or("unknown");
    if (name.length() > 19) {
        name = name.substr(0, 17) + "..";
    }
    
    // Version
    std::string version = "N/A";
    for (const auto& [key, value] : pkg.attributes) {
        if (key == "version") {
            version = value;
            break;
        }
    }
    if (version.length() > 18) {
        version = version.substr(0, 16) + "..";
    }
    
    // State
    std::string state = "unknown";
    for (const auto& [key, value] : pkg.attributes) {
        if (key == "state") {
            state = value;
            break;
        }
    }
    if (state.length() > 13) {
        state = state.substr(0, 11) + "..";
    }
    
    std::cout << name << "  ";
    std::cout << version << "  ";
    std::cout << state << "  ";
    
    // Source
    if (pkg.freshness.source_kind == inventory::FreshnessReport::Source::kUnknown) {
        std::cout << "unknown";
    } else {
        std::string src = pkg.freshness.source;
        if (src.length() > 10) {
            src = src.substr(0, 8) + "..";
        }
        std::cout << src;
    }
    
    std::cout << "  ";
    
    // Freshness
    if (pkg.freshness.source_kind == inventory::FreshnessReport::Source::kUnknown) {
        std::cout << "unknown";
    } else if (pkg.freshness.is_stale) {
        std::cout << "STALE(" << format_freshness(pkg.freshness) << ")";
    } else {
        std::cout << "OK(" << format_freshness(pkg.freshness) << ")";
    }
    
    // Verbose: show additional info
    if (verbose) {
        std::cout << "\n  [id: " << pkg.id;
        std::cout << ", source_kind: " << static_cast<int>(pkg.freshness.source_kind);
        if (pkg.freshness.observed_at.time_since_epoch().count() != 0) {
            auto epoch = pkg.freshness.observed_at.time_since_epoch();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
            std::cout << ", observed_at: " << ms;
        }
        std::cout << "]";
    }
    
    std::cout << "\n";
}

int cmd_inventory_packages_json(const inventory::QueryOptions& options, const rebuntu::cli::inventory::QueryResult& result) {
    auto generator = rebuntu::system::observation::output::make_output_generator();
    
    rebuntu::system::observation::output::OutputOptions output_options;
    output_options.max_records = options.max_results > 0 ? options.max_results : 1000;
    output_options.include_statistics = true;
    
    if (!generator->configure(output_options).is_success()) {
        std::cerr << "error: failed to configure output generator\n";
        return 1;
    }
    
    for (const auto& pkg : result.entities) {
        rebuntu::system::observation::output::ObservationRecord record;
        
        // Build observation record from EntityInfo
        record.id = pkg.id;
        if (pkg.name.has_value()) {
            record.name = pkg.name.value();
        }
        record.category = "package";
        record.state = rebuntu::system::observation::output::ObservationRecord::State::kActive;  // Default active state
        
        // Add package attributes
        for (const auto& [key, value] : pkg.attributes) {
            record.attributes[key] = value;
        }
        
        // Build observation values from freshness report
        if (pkg.freshness.source_kind != rebuntu::cli::inventory::FreshnessReport::Source::kUnknown) {
            rebuntu::system::observation::output::ObservationValue obs;
            obs.source = pkg.freshness.source;
            
            // Format observed_at as ISO-8601
            auto tt = std::chrono::system_clock::to_time_t(pkg.freshness.observed_at);
            char buf[32];
            strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", gmtime(&tt));
            obs.value = pkg.freshness.source + ":" + std::string(buf) + 
                       (pkg.freshness.is_stale ? ":stale" : ":fresh");
            
            record.observations.push_back(std::move(obs));
        }
        
        if (!generator->add_record(std::move(record)).is_success()) {
            // Output was truncated due to bounds
            break;
        }
    }
    
    std::cout << generator->generate();
    return 0;
}

int cmd_inventory_packages(const inventory::QueryOptions& options) {
    auto query = rebuntu::cli::inventory::make_inventory_query();
    if (!query) {
        std::cerr << "error: failed to create inventory query\n";
        return 1;
    }
    
    auto result = query->query_all(options);
    
    switch (result.status) {
        case core::SemanticStatus::kSuccess:
            break;
        case core::SemanticStatus::kFailure:
            std::cerr << "error: " << result.description << "\n";
            return 1;
        default:
            std::cerr << "error: " << result.description << "\n";
            return 1;
    }
    
    if (result.entities.empty()) {
        std::cout << "No packages found.\n";
        return 0;
    }
    
    // Check if JSON output is requested via command line option parsing
    bool json_output = false;  // For now, always use table format (CLI --format not fully implemented yet)
    
    if (json_output) {
        return cmd_inventory_packages_json(options, result);
    }
    
    print_package_header();
    
    for (const auto& pkg : result.entities) {
        print_package(pkg, options.kind == inventory::InventoryKind::kUnknown);
    }
    
    // Print summary
    std::cout << "\n" << result.total_found << " packages total\n";
    if (result.fresh_count > 0 || result.stale_count > 0) {
        std::cout << "fresh: " << result.fresh_count << ", stale: " << result.stale_count << "\n";
    }
    
    return 0;
}

// ============================================================================
// main — CLI entry point with parser boundary (Task 6.46)
//
// This is the interface edge where text parsing happens:
//   argv → tokenize/parse_argv → typed CommandIntent
//
// Domain code receives ONLY typed structures - no string re-parsing.
// ============================================================================

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }
    
    // Check for help flag before parsing (help is special case)
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "help" || arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            return 0;
        }
    }
    
    // Build vector of arguments from raw argv (interface edge - text parsing)
    std::vector<std::string> args(argv, argv + argc);
    
    // Parse at the boundary: argv → typed CommandIntent
    parser::ParseError parse_error{};
    shell::CommandIntent intent = parser::parse_argv(args, parse_error);
    
    if (!parse_error.message.empty()) {
        std::cerr << "error: " << parse_error.message << "\n";
        print_usage(argv[0]);
        return 1;
    }
    
    // Command intent is now typed - no more string parsing in dispatch logic
    const std::string& command = intent.verb;
    
    if (command == "inventory" || command == "pkg" || command == "package") {
        // Default to packages
        inventory::QueryOptions options;
        
        // Extract options from qualifiers map (already typed, no re-parsing)
        auto it = intent.qualifiers.find("freshness");
        if (it != intent.qualifiers.end()) {
            try {
                options.freshness_threshold_ms = std::chrono::seconds(std::stoi(it->second));
            } catch (...) {}
        }
        
        it = intent.qualifiers.find("max");
        if (it != intent.qualifiers.end()) {
            try {
                options.max_results = std::stoul(it->second);
            } catch (...) {}
        }
        
        // Handle "all" qualifier for all packages
        if (intent.qualifiers.count("all") > 0) {
            options.kind = inventory::InventoryKind::kPackage;
        } else {
            // Check positional arguments for package kind
            if (!intent.arguments.empty()) {
                std::string arg = intent.arguments[0].second;
                if (arg == "packages" || arg == "pkg") {
                    options.kind = inventory::InventoryKind::kPackage;
                }
            }
        }
        
        return cmd_inventory_packages(options);
    } else if (command == "help" || command == "--help" || command == "-h") {
        print_usage(argv[0]);
        return 0;
    } else {
        std::cerr << "error: unknown command: " << command << "\n";
        print_usage(argv[0]);
        return 1;
    }
}

}  // namespace rebuntu::cli

int main(int argc, char** argv) {
    return rebuntu::cli::main(argc, argv);
}