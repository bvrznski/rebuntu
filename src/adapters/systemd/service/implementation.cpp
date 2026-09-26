// rebuntu::adapters::systemd::service — Systemd Service Discovery Implementation (Phase 5.26)
//
// This module implements the systemd-based service discovery adapter:
//   - Observes systemd units through native systemctl interface
//   - Provides bounded, freshness-aware observation of service state

#include "adapters/systemd/service/types.hpp"

#include <array>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <cstring>

namespace rebuntu::adapters::systemd::service {

// ============================================================================
// Helper: Read command output
// ============================================================================

static std::string read_command_output(const char* command) {
    std::array<char, 4096> buffer;
    std::string result;
    
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        return "";
    }
    
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
        result += buffer.data();
    }
    
    pclose(pipe);
    return result;
}

// ============================================================================
// Helper: Split string by delimiter
// ============================================================================

static std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    
    while (std::getline(iss, token, delimiter)) {
        // Trim whitespace
        size_t start = token.find_first_not_of(" \t\r\n");
        if (start != std::string::npos) {
            size_t end = token.find_last_not_of(" \t\r\n");
            tokens.push_back(token.substr(start, end - start + 1));
        }
    }
    
    return tokens;
}

// ============================================================================
// Helper: Parse systemctl list-units output
//
// Format: UNIT LOAD ACTIVE SUB DESCRIPTION TYPE SOURCE
// Example: apache2.service loaded active running The Apache HTTP Server service /lib/systemd/system/apache2.service
// ============================================================================

static std::vector<ServiceIdentity> parse_unit_list(const std::string& output) {
    std::vector<ServiceIdentity> identities;
    
    auto lines = split_string(output, '\n');
    
    for (const auto& line : lines) {
        if (line.empty()) continue;
        
        // Split by whitespace
        auto tokens = split_string(line, ' ');
        
        if (tokens.size() >= 2) {
            // First token is unit name with type suffix
            std::string unit_name = tokens[0];
            
            // Extract type from the end (e.g., .service, .socket)
            ServiceIdentity identity;
            identity.name = unit_name;
            
            // Determine type based on suffix
            if (unit_name.size() > 8 && unit_name.substr(unit_name.size() - 8) == ".service") {
                identity.type = "service";
            } else if (unit_name.size() > 6 && unit_name.substr(unit_name.size() - 6) == ".socket") {
                identity.type = "socket";
            } else if (unit_name.size() > 5 && unit_name.substr(unit_name.size() - 5) == ".timer") {
                identity.type = "timer";
            } else if (unit_name.size() > 7 && unit_name.substr(unit_name.size() - 7) == ".target") {
                identity.type = "target";
            } else {
                identity.type = "unknown";
            }
            
            identities.push_back(identity);
        }
    }
    
    return identities;
}

// ============================================================================
// Helper: Parse systemctl show output for a single unit
//
// Format: PROPERTY=VALUE pairs
// ============================================================================

static std::optional<ServiceObservation> parse_unit_show(
    const ServiceIdentity& identity,
    const std::string& output) {
    
    ServiceObservation observation;
    observation.identity = identity;
    observation.observed_at = std::chrono::system_clock::now();
    observation.source = "systemd";
    
    auto lines = split_string(output, '\n');
    
    for (const auto& line : lines) {
        if (line.empty()) continue;
        
        auto eq_pos = line.find('=');
        if (eq_pos == std::string::npos) continue;
        
        std::string key = line.substr(0, eq_pos);
        std::string value = line.substr(eq_pos + 1);
        
        // Parse common properties
        if (key == "Id") {
            // Already set from identity
        } else if (key == "Description") {
            observation.description = value;
        } else if (key == "ActiveState") {
            if (value == "active") {
                observation.active_state = ServiceActiveState::kActive;
            } else if (value == "inactive") {
                observation.active_state = ServiceActiveState::kInactive;
            } else if (value == "activating") {
                observation.active_state = ServiceActiveState::kActivating;
            } else if (value == "deactivating") {
                observation.active_state = ServiceActiveState::kDeactivating;
            } else if (value == "failed") {
                observation.active_state = ServiceActiveState::kFailed;
            }
        } else if (key == "SubState") {
            // Substate depends on unit type; just record the raw value for now
            if (value == "running" || value == "reloading") {
                observation.sub_state = ServiceSubState::kRunning;
            } else if (value == "dead" || value == "stop-sigterm" || 
                       value == "stop-signals" || value == "stop-watchdog" ||
                       value == "stop-killed" || value == "stop-post" ||
                       value == "final-watchdog" || value == "final-sigterm" ||
                       value == "final-sigkill") {
                observation.sub_state = ServiceSubState::kDead;
            } else if (value == "start" || value == "start-pre" || 
                       value == "start-post") {
                observation.sub_state = ServiceSubState::kStart;
            } else if (value == "stop" || value == "stop-notifyfd") {
                observation.sub_state = ServiceSubState::kStop;
            } else if (value == "reload") {
                observation.sub_state = ServiceSubState::kReload;
            } else if (value == "restart" || value == "restart-signal" ||
                       value == "restart-watchdog") {
                observation.sub_state = ServiceSubState::kRestart;
            }
        } else if (key == "UnitFileState") {
            if (value == "enabled") {
                observation.unit_state = ServiceUnitState::kEnabled;
            } else if (value == "disabled") {
                observation.unit_state = ServiceUnitState::kDisabled;
            } else if (value == "static") {
                observation.unit_state = ServiceUnitState::kStatic;
            } else if (value == "indirect") {
                observation.unit_state = ServiceUnitState::kIndirect;
            } else if (value == "masked") {
                observation.unit_state = ServiceUnitState::kMasked;
            }
        } else if (key == "MainPID" || key == "ExecMainPID") {
            try {
                int64_t pid = std::stoll(value);
                if (pid > 0 && !observation.runtime.has_value()) {
                    observation.runtime.emplace();
                }
                if (pid > 0 && observation.runtime.has_value()) {
                    if (key == "MainPID") {
                        observation.runtime->main_pid = pid;
                    } else {
                        observation.runtime->exec_main_pid = pid;
                    }
                }
            } catch (...) {}
        } else if (key == "FragmentPath") {
            observation.fragment_path = value;
        } else if (key == "SourcePath") {
            observation.source_path = value;
        }
    }
    
    // Only return valid observations
    if (!observation.identity.is_valid()) {
        return std::nullopt;
    }
    
    return observation;
}

// ============================================================================
// ServiceDiscoveryAdapter Implementation
// ============================================================================

class SystemdServiceDiscoveryAdapter : public ServiceDiscoveryAdapter {
public:
    SystemdServiceDiscoveryAdapter() = default;
    ~SystemdServiceDiscoveryAdapter() override = default;
    
    ServiceDiscoveryResult observe_all_services() override {
        ServiceDiscoveryResult result;
        result.observed_at = std::chrono::system_clock::now();
        auto start_time = std::chrono::steady_clock::now();
        
        // Get list of all units
        std::string list_output = read_command_output(
            "systemctl list-units --type=service,socket,timer,target --no-legend --plain 2>/dev/null");
        
        if (list_output.empty()) {
            result.status = core::SemanticStatus::kUnknown;
            result.description = "Failed to get unit list from systemctl";
            return result;
        }
        
        auto identities = parse_unit_list(list_output);
        
        // Observe each unit
        for (const auto& identity : identities) {
            std::string show_command = "systemctl show --property=Id,Description,ActiveState,"
                "SubState,UnitFileState,MainPID,ExecMainPID,FragmentPath,SourcePath \"" + 
                identity.name + "\" 2>/dev/null";
            
            std::string show_output = read_command_output(show_command.c_str());
            
            auto observation = parse_unit_show(identity, show_output);
            
            if (observation) {
                result.services.push_back(std::move(*observation));
                
                // Update statistics
                result.total_services++;
                
                switch (result.services.back().active_state) {
                    case ServiceActiveState::kActive:
                        result.active_services++;
                        break;
                    case ServiceActiveState::kInactive:
                        result.inactive_services++;
                        break;
                    case ServiceActiveState::kFailed:
                        result.failed_services++;
                        break;
                    default:
                        result.other_services++;
                        break;
                }
                
                switch (result.services.back().unit_state) {
                    case ServiceUnitState::kEnabled:
                        result.enabled_units++;
                        break;
                    case ServiceUnitState::kDisabled:
                        result.disabled_units++;
                        break;
                    case ServiceUnitState::kMasked:
                        result.masked_units++;
                        break;
                    default:
                        // Other states don't have counters
                        break;
                }
            } else {
                result.errors.emplace_back(identity.name, core::Error{
                    "E_PARSE_FAILURE",
                    "Failed to parse unit properties"
                });
            }
        }
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.provider_source = "systemd";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully discovered units from systemd";
        
        last_observation_time_ = result.observed_at;
        
        return result;
    }
    
    std::optional<ServiceObservation> observe_service(
        const ServiceIdentity& identity) override {
        
        if (!identity.is_valid()) {
            return std::nullopt;
        }
        
        std::string show_command = "systemctl show --property=Id,Description,ActiveState,"
            "SubState,UnitFileState,MainPID,ExecMainPID,FragmentPath,SourcePath \"" + 
            identity.name + "\" 2>/dev/null";
        
        std::string output = read_command_output(show_command.c_str());
        
        if (output.empty()) {
            return std::nullopt;
        }
        
        auto observation = parse_unit_show(identity, output);
        
        if (observation) {
            observation->observed_at = std::chrono::system_clock::now();
            observation->source = "systemd";
        }
        
        return observation;
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }
    
    ServiceDiscoveryResult force_refresh() override {
        last_observation_time_ = {};
        return observe_all_services();
    }

private:
    std::chrono::system_clock::time_point last_observation_time_{};
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ServiceDiscoveryAdapter> make_systemd_service_discovery_adapter() {
    return std::make_unique<SystemdServiceDiscoveryAdapter>();
}

}  // namespace rebuntu::adapters::systemd::service