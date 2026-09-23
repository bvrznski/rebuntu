#include "cli.hpp"

#include <runtime/core/contracts.hpp>
#include <runtime/core/version.hpp>
#include <runtime/lifecycle/contracts.hpp>
#include <semantics/service.hpp>

#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <sstream>

namespace rebuntu::cli {
namespace {

using core::Component;
using core::ComponentKind;
using core::ComponentRegistry;

void print_banner(std::ostream& os) {
    os << "Rebuntu " << core::kVersion
       << "  (phase " << core::kPhase
       << ")  —  C++-native Linux system-management environment\n";
    os << "Primary package: `system` (src/system)   Build: "
       << REBUNTU_BUILD_CONFIG << "\n\n";
}

void print_components(std::ostream& os) {
    // The initial structural registry: the Phase 0.0 skeleton described as
    // DATA. It is not a runtime; it records what exists and what depends on
    // what, and is verified by ComponentRegistry::validate().
    ComponentRegistry reg;
    reg.register_component(
        {"system.core", ComponentKind::kModule, "Core",
         "Foundational contracts and semantic primitives (Result/Outcome/Evidence, "
         "ComponentRegistry). No I/O, no runtime.", "", {}});
    reg.register_component(
        {"system.shell", ComponentKind::kModule, "Shell",
         "Interactive command environment and shell-facing interface (reserved; "
         "not implemented in Phase 0.0).", "", {"system.core"}});
    reg.register_component(
        {"system.runtime", ComponentKind::kModule, "Runtime",
         "Runtime/execution foundation (reserved; not implemented in Phase 0.0).",
         "", {"system.core"}});
    reg.register_component(
        {"system.state", ComponentKind::kModule, "State",
         "Authoritative state management (reserved; not implemented in Phase 0.0).",
         "", {"system.core"}});
    reg.register_component(
        {"system.environment", ComponentKind::kModule, "Environment",
         "Host environment observation (reserved; not implemented in Phase 0.0).",
         "procfs / sysfs / cgroups v2", {"system.core"}});

    const auto issues = reg.validate();
    if (!issues.empty()) {
        os << "structural validation FAILED:\n";
        for (const auto& i : issues) os << "  - " << i << "\n";
    }

    os << "Registered components (" << reg.size() << "):\n";
    for (const auto& c : reg.all()) {
        os << "  [" << core::to_string(c.kind) << "] " << c.id << "  —  " << c.title;
        if (!c.native_mechanism.empty()) {
            os << "   (native: " << c.native_mechanism << ")";
        }
        os << "\n";
        if (!c.purpose.empty()) os << "        " << c.purpose << "\n";
        if (!c.depends_on.empty()) {
            os << "        depends_on: ";
            for (std::size_t k = 0; k < c.depends_on.size(); ++k) {
                if (k) os << ", ";
                os << c.depends_on[k];
            }
            os << "\n";
        }
    }
}

void print_help(std::ostream& os) {
    print_banner(os);
    os << "Usage:\n"
       << "  rebuntu <command> [options]\n\n"
       << "Commands (Phase 0.0 — structural skeleton only):\n"
       << "  help        Show this help\n"
       << "  version     Show version and phase\n"
       << "  components  List the initial structural registry\n\n"
       << "Commands (Phase 1.11 — lifecycle management):\n"
       << "  reconfigure Change configuration without reinstalling\n"
       << "  repair      Restore Rebuntu-owned artifacts to correct state\n"
       << "  upgrade     Migrate between versions\n"
       << "  uninstall   Remove Rebuntu-owned artifacts (preserve user data)\n"
       << "  purge       Remove everything including user configuration\n\n"
       << "Phase 0.0 is an architectural bootstrap: no system-management\n"
       << "capability is implemented yet. See docs/README.md and\n"
       << "docs/ROADMAP.md for the current and planned state.\n";
}

// Parse config key=value pairs into a map
std::map<std::string, std::string> parse_config(const std::vector<std::string>& args) {
    std::map<std::string, std::string> config;
    for (const auto& arg : args) {
        size_t eq_pos = arg.find('=');
        if (eq_pos != std::string::npos) {
            std::string key = arg.substr(0, eq_pos);
            std::string value = arg.substr(eq_pos + 1);
            config[key] = value;
        }
    }
    return config;
}

// Print lifecycle result to ostream
void print_result(std::ostream& os, const lifecycle::LifecycleResult& result) {
    os << "Operation: " << lifecycle::to_string(result.operation) << "\n";
    os << "Status: " << lifecycle::to_string(result.status) << "\n";
    os << "Success: " << (result.success ? "yes" : "no") << "\n";
    os << "Verified: " << (result.verified ? "yes" : "no") << "\n";

    if (!result.operations.empty()) {
        os << "\nOperations:\n";
        for (const auto& op : result.operations) {
            os << "  " << lifecycle::to_string(op.action) << ": " << op.path;
            if (op.error_code.has_value()) {
                os << " [" << op.error_code.value() << "]";
            }
            if (op.error_message.has_value()) {
                os << " - " << op.error_message.value();
            }
            os << "\n";
        }
    }

    if (!result.created_paths.empty()) {
        os << "\nCreated:\n";
        for (const auto& path : result.created_paths) {
            os << "  " << path << "\n";
        }
    }

    if (!result.deleted_paths.empty()) {
        os << "\nDeleted:\n";
        for (const auto& path : result.deleted_paths) {
            os << "  " << path << "\n";
        }
    }

    if (result.error.has_value()) {
        os << "\nError: " << result.error.value().code << " - " 
           << result.error.value().message << "\n";
    }
}

}  // namespace

int run(std::span<const char* const> argv) {
    std::ios::sync_with_stdio(false);
    std::ostream& os = std::cout;

    if (argv.empty() || std::string_view(argv[0]) == "-h" ||
        std::string_view(argv[0]) == "--help" || std::string_view(argv[0]) == "help") {
        print_help(os);
        return 0;
    }

    std::string_view cmd(argv[0]);

    if (cmd == "version" || cmd == "--version") {
        print_banner(os);
        os << "version: " << core::kVersion
           << "\nphase:   " << core::kPhase
           << "\npackage: " << core::kPackageName << "\n";
        return 0;
    }

    if (cmd == "components" || cmd == "component") {
        print_components(os);
        return 0;
    }

    // Phase 1.11: Lifecycle operations
    if (cmd == "reconfigure") {
        // Check for help flags first
        bool has_help = false;
        std::vector<std::string> non_help_args;
        
        for (size_t i = 1; i < argv.size(); ++i) {
            std::string_view arg(argv[i]);
            if (arg == "--help" || arg == "-h") {
                has_help = true;
            } else {
                non_help_args.push_back(std::string(arg));
            }
        }
        
        if (has_help) {
            os << "Usage:\n"
               << "  rebuntu reconfigure <key=value> [key2=value2...]\n\n"
               << "Change Rebuntu configuration without reinstalling.\n";
            return 0;
        }
        
        if (non_help_args.empty()) {
            os << "Usage:\n"
               << "  rebuntu reconfigure <key=value> [key2=value2...]\n\n"
               << "Change Rebuntu configuration without reinstalling.\n";
            return 1;
        }

        // Collect config arguments
        auto config = parse_config(non_help_args);

        lifecycle::LifecycleContext ctx;
        ctx.dry_run = false;

        auto result = lifecycle::reconfigure(ctx, config);
        print_result(os, result);

        return result.success ? 0 : 1;
    }

    if (cmd == "repair") {
        // Check for help flags first
        bool has_help = false;
        std::vector<std::string> non_help_args;
        
        for (size_t i = 1; i < argv.size(); ++i) {
            std::string_view arg(argv[i]);
            if (arg == "--help" || arg == "-h") {
                has_help = true;
            } else if (arg == "--dry-run" || arg == "-n") {
                // Skip dry-run, we'll always use it when parsing
            } else if (!arg.empty() && arg[0] != '-') {
                non_help_args.push_back(std::string(arg));
            }
        }
        
        if (has_help) {
            os << "Usage:\n"
               << "  rebuntu repair [path1 path2...]\n\n"
               << "Restore Rebuntu-owned artifacts to correct state.\n";
            return 0;
        }

        // Parse path arguments
        std::vector<std::string> paths = non_help_args;
        
        bool has_dry_run = false;
        for (size_t i = 1; i < argv.size(); ++i) {
            std::string_view arg(argv[i]);
            if (arg == "--dry-run" || arg == "-n") {
                has_dry_run = true;
            }
        }
        
        lifecycle::LifecycleContext ctx;
        ctx.dry_run = has_dry_run;

        auto result = lifecycle::repair(ctx, paths);
        print_result(os, result);

        return result.success ? 0 : 1;
    }

    if (cmd == "upgrade") {
        // Check for help flags first
        bool has_help = false;
        
        for (size_t i = 1; i < argv.size(); ++i) {
            std::string_view arg(argv[i]);
            if (arg == "--help" || arg == "-h") {
                has_help = true;
            }
        }
        
        if (has_help) {
            os << "Usage:\n"
               << "  rebuntu upgrade <target-version>\n\n"
               << "Migrate from current version to target version.\n";
            return 0;
        }
        
        if (argv.size() < 2) {
            os << "Usage:\n"
               << "  rebuntu upgrade <target-version>\n\n"
               << "Migrate from current version to target version.\n";
            return 1;
        }

        std::string target_version(argv[1]);
        lifecycle::LifecycleContext ctx;

        auto result = lifecycle::upgrade(ctx, target_version);
        print_result(os, result);

        return result.success ? 0 : 1;
    }

    if (cmd == "uninstall") {
        bool has_dry_run = false;
        bool has_force = false;

        for (size_t i = 1; i < argv.size(); ++i) {
            std::string_view arg(argv[i]);
            if (arg == "--dry-run" || arg == "-n") {
                has_dry_run = true;
            } else if (arg == "--force" || arg == "-f") {
                has_force = true;
            }
        }

        lifecycle::LifecycleContext ctx;
        ctx.dry_run = has_dry_run;
        ctx.force = has_force;

        auto result = lifecycle::uninstall(ctx);
        print_result(os, result);

        return result.success ? 0 : 1;
    }

    if (cmd == "purge") {
        bool has_dry_run = false;

        for (size_t i = 1; i < argv.size(); ++i) {
            std::string_view arg(argv[i]);
            if (arg == "--dry-run" || arg == "-n") {
                has_dry_run = true;
            }
        }

        lifecycle::LifecycleContext ctx;
        ctx.dry_run = has_dry_run;

        auto result = lifecycle::purge(ctx);
        print_result(os, result);

        return result.success ? 0 : 1;
    }

    // Phase 3.3: Semantic service management
    if (cmd == "semantic" || cmd == "sem") {
        bool has_help = false;
        std::vector<std::string> subcommands;

        for (size_t i = 1; i < argv.size(); ++i) {
            std::string_view arg(argv[i]);
            if (arg == "--help" || arg == "-h") {
                has_help = true;
            } else if (arg[0] != '-') {
                subcommands.push_back(std::string(arg));
            }
        }

        if (has_help || subcommands.empty()) {
            os << "Usage:\n"
               << "  rebuntu semantic <command> [options]\n\n"
               << "Semantic service management commands:\n"
               << "  status    Show service state and readiness\n"
               << "  start     Start the semantic service\n"
               << "  stop      Stop the semantic service\n"
               << "  restart   Restart the semantic service\n"
               << "  check     Perform a readiness check\n"
               << "  classify  Run a classification request (for testing)\n"
               << "\nOptions:\n"
               << "  --help, -h    Show this help message\n";
            return 0;
        }

        std::string_view subcmd = subcommands[0];

        if (subcmd == "status") {
            // For now, use a mock controller to show state
            semantic::service::Config cfg;
            cfg.ipc_socket_path = "/run/user/" + std::to_string(getuid()) + 
                                  "/rebuntu-semantic.sock";
            // Use empty model_path for testing (will be available after start)
            
            semantic::service::MockServiceController ctrl(cfg);
            
            os << "Semantic Service Status\n"
               << "=======================\n";
            os << "State:     " << semantic::service::to_string(ctrl.get_state()) << "\n";
            os << "Readiness: " << semantic::service::to_string(ctrl.get_readiness()) << "\n";
            os << "Healthy:   " << (ctrl.is_healthy() ? "yes" : "no") << "\n";
            
            return 0;
        }

        if (subcmd == "start") {
            semantic::service::Config cfg;
            semantic::service::MockServiceController ctrl(cfg);
            
            bool started = ctrl.start();
            os << "Starting semantic service... " 
               << (started ? "OK" : "FAILED") << "\n";
            return started ? 0 : 1;
        }

        if (subcmd == "stop") {
            semantic::service::Config cfg;
            semantic::service::MockServiceController ctrl(cfg);
            
            bool stopped = ctrl.stop();
            os << "Stopping semantic service... " 
               << (stopped ? "OK" : "FAILED") << "\n";
            return stopped ? 0 : 1;
        }

        if (subcmd == "restart") {
            semantic::service::Config cfg;
            semantic::service::MockServiceController ctrl(cfg);
            
            bool restarted = ctrl.restart();
            os << "Restarting semantic service... " 
               << (restarted ? "OK" : "FAILED") << "\n";
            return restarted ? 0 : 1;
        }

        if (subcmd == "check") {
            semantic::service::Config cfg;
            semantic::service::MockServiceController ctrl(cfg);
            
            bool ready = (ctrl.get_readiness() == semantic::service::ReadinessState::kReady);
            os << "Semantic service readiness: "
               << (ready ? "READY" : "NOT READY") << "\n";
            return ready ? 0 : 1;
        }

        if (subcmd == "classify") {
            // Test classification request
            semantic::service::Config cfg;
            semantic::service::MockServiceController ctrl(cfg);
            
            semantic::service::SemanticRequest req;
            req.type = semantic::service::SemanticRequestType::kClassification;
            req.timestamp = std::chrono::system_clock::now();
            req.classification.input = "cpu usage high";
            req.classification.categories = {"normal", "high", "critical"};
            
            auto result = ctrl.send_request(req);
            
            os << "Classification Result\n"
               << "====================\n";
            
            if (result.status == core::SemanticStatus::kSuccess && 
                result.response.has_value()) {
                const auto& resp = *result.response;
                if (resp.data.classification.has_value()) {
                    for (const auto& [label, conf] : resp.data.classification->categories) {
                        os << "  " << label << ": " << (conf * 100.0) << "%\n";
                    }
                }
            } else {
                // Use core::to_string for SemanticStatus
                std::string status_str;
                switch (result.status) {
                    case core::SemanticStatus::kSuccess:   status_str = "success"; break;
                    case core::SemanticStatus::kCompleted: status_str = "completed"; break;
                    case core::SemanticStatus::kFailure:   status_str = "failure"; break;
                    case core::SemanticStatus::kUnknown:   status_str = "unknown"; break;
                    case core::SemanticStatus::kCancelled: status_str = "cancelled"; break;
                }
                
                os << "Error: ";
                if (result.error.has_value()) {
                    os << result.error->code << " - " << result.error->message;
                } else {
                    os << status_str;
                }
                os << "\n";
            }
            
            return 0;
        }

        os << "Unknown semantic command: " << subcmd << "\n\n";
        os << "Run 'rebuntu semantic --help' for usage.\n";
        return 1;
    }

    // Unknown command: a typed, non-booleans failure with a stable code.
    os << "rebuntu: unknown command '" << cmd << "'\n\n";
    print_help(os);
    return 1;
}

}  // namespace rebuntu::cli