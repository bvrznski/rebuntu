// rebuntu::environment::capability_state — Linux Capabilities Implementation (Phase 2.5)
#include <observation/environment/capability_state.hpp>

#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdint>
#include <cerrno>
#include <climits>
#include <sys/prctl.h>

// Include libcap if available
#if defined(__linux__) && (defined(HAVE_SYS_CAPABILITY_H) || \
    (defined(__has_include) && __has_include(<sys/capability.h>)))
#define HAVE_LIBCAP 1
#include <sys/capability.h>
#endif

namespace rebuntu::environment::capability_state {

// ============================================================================
// Bitmask parsing from procfs hex string
// ============================================================================

static CapabilityBitmask parse_hex_bitmask(const std::string& hex_str) {
    CapabilityBitmask result = make_empty_bitmask();
    
    size_t len = hex_str.length();
    if (len == 0) return result;
    
    std::string padded = hex_str;
    while (padded.length() < 16) {
        padded = "0" + padded;
    }
    
    if (padded.length() >= 8) {
        uint32_t high_bits = 0;
        std::istringstream iss_high(padded.substr(0, 8));
        iss_high >> std::hex >> high_bits;
        result[1] = high_bits;
    }
    
    if (padded.length() >= 16) {
        uint32_t low_bits = 0;
        std::istringstream iss_low(padded.substr(8, 8));
        iss_low >> std::hex >> low_bits;
        result[0] = low_bits;
    }
    
    return result;
}

// ============================================================================
// Helper: starts_with for C++17 compatibility
// ============================================================================

static bool starts_with(const std::string& str, const char* prefix) {
    size_t prefix_len = strlen(prefix);
    if (prefix_len > str.length()) return false;
    return strncmp(str.c_str(), prefix, prefix_len) == 0;
}

// ============================================================================
// Observation: discover_capability_state() - Read /proc/self/status
// ============================================================================

ProcessCapabilityState discover_capability_state() {
    ProcessCapabilityState state;
    state.pid = 0;
    
    std::ifstream proc_status("/proc/self/status");
    if (!proc_status.is_open()) {
        return state;
    }
    
    std::string line;
    while (std::getline(proc_status, line)) {
        if (line.length() < 8) continue;
        
        const char* prefix = nullptr;
        std::string value_str;
        
        if (starts_with(line, "CapPrm")) {
            prefix = "CapPrm";
            size_t pos = line.find('\t');
            if (pos != std::string::npos) {
                value_str = line.substr(pos + 1);
            }
        } else if (starts_with(line, "CapEff")) {
            prefix = "CapEff";
            size_t pos = line.find('\t');
            if (pos != std::string::npos) {
                value_str = line.substr(pos + 1);
            }
        } else if (starts_with(line, "CapInh")) {
            prefix = "CapInh";
            size_t pos = line.find('\t');
            if (pos != std::string::npos) {
                value_str = line.substr(pos + 1);
            }
        } else if (starts_with(line, "CapBnd")) {
            prefix = "CapBnd";
            size_t pos = line.find('\t');
            if (pos != std::string::npos) {
                value_str = line.substr(pos + 1);
            }
        } else if (starts_with(line, "CapAmb")) {
            prefix = "CapAmb";
            size_t pos = line.find('\t');
            if (pos != std::string::npos) {
                value_str = line.substr(pos + 1);
            }
        }
        
        if (prefix && !value_str.empty()) {
            CapabilityBitmask mask = parse_hex_bitmask(value_str);
            
            if (strcmp(prefix, "CapPrm") == 0) {
                state.sets.permitted = mask;
            } else if (strcmp(prefix, "CapEff") == 0) {
                state.sets.effective = mask;
            } else if (strcmp(prefix, "CapInh") == 0) {
                state.sets.inheritable = mask;
            } else if (strcmp(prefix, "CapBnd") == 0) {
                state.sets.bounding = mask;
            } else if (strcmp(prefix, "CapAmb") == 0) {
                state.sets.ambient = mask;
            }
        }
    }
    
    proc_status.close();
    return state;
}

// ============================================================================
// Observation: has_effective_capability()
// ============================================================================

bool has_effective_capability(Capability c) {
    ProcessCapabilityState state = discover_capability_state();
    return has_capability(state.sets.effective, c);
}

// ============================================================================
// Observation: get_permitted_set()
// ============================================================================

std::set<Capability> get_permitted_set() {
    ProcessCapabilityState state = discover_capability_state();
    return capabilities_from_bitmask(state.sets.permitted);
}

// ============================================================================
// Observation: getBoundingBitmask()
// Return the bounding set as a bitmask (not converted to set)
// ============================================================================

static CapabilityBitmask getBoundingBitmask() {
    ProcessCapabilityState state = discover_capability_state();
    return state.sets.bounding;
}

// ============================================================================
// Observation: getBoundingSet()
// Return the bounding set as a std::set<Capability> for convenience
// ============================================================================

std::set<Capability> getBoundingSet() {
    return capabilities_from_bitmask(getBoundingBitmask());
}

// ============================================================================
// File Capability Operations
// ============================================================================

#ifdef HAVE_LIBCAP

std::optional<FileCapabilityState> get_file_capabilities(const std::string& path) {
    cap_t caps = cap_get_file(path.c_str());
    if (!caps) {
        return std::nullopt;
    }
    
    FileCapabilityState state;
    cap_free(caps);
    return state;
}

bool set_file_capabilities(const std::string& path, const FileCapabilityState& state) {
    (void)path;
    (void)state;
    return false;
}

#else

std::optional<FileCapabilityState> get_file_capabilities(const std::string& path) {
    (void)path;
    return std::nullopt;
}

bool set_file_capabilities(const std::string& path, const FileCapabilityState& state) {
    (void)path;
    (void)state;
    return false;
}

#endif  // HAVE_LIBCAP

// ============================================================================
// Ambient Capability Management
// ============================================================================

bool add_ambient_capability(Capability c) {
    unsigned long cap_val = static_cast<unsigned long>(c);
    if (!prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap_val, 0, 0)) {
        return true;
    }
    return false;
}

bool remove_ambient_capability(Capability c) {
    unsigned long cap_val = static_cast<unsigned long>(c);
    if (!prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_LOWER, cap_val, 0, 0)) {
        return true;
    }
    return false;
}

std::set<Capability> get_ambient_set() {
    auto state = discover_capability_state();
    return capabilities_from_bitmask(state.sets.ambient);
}

// ============================================================================
// Process Capability Management
// ============================================================================

#ifdef HAVE_LIBCAP

bool drop_capability(Capability c) {
    cap_t caps = cap_get_pid(0);
    if (!caps) {
        return false;
    }
    
    bool success = true;
    unsigned long cap_val = static_cast<unsigned long>(c);
    
    if (cap_set_flag(caps, CAP_EFFECTIVE, 1, &cap_val, CAP_CLEAR) != 0) {
        success = false;
    }
    if (cap_set_flag(caps, CAP_PERMITTED, 1, &cap_val, CAP_CLEAR) != 0) {
        success = false;
    }
    if (cap_set_flag(caps, CAP_INHERITABLE, 1, &cap_val, CAP_CLEAR) != 0) {
        success = false;
    }
    
    if (success && cap_set_proc(caps) != 0) {
        success = false;
    }
    
    cap_free(caps);
    return success;
}

bool enable_effective_capability(Capability c) {
    cap_t caps = cap_get_pid(0);
    if (!caps) {
        return false;
    }
    
    bool success = true;
    unsigned long cap_val = static_cast<unsigned long>(c);
    
    if (cap_set_flag(caps, CAP_EFFECTIVE, 1, &cap_val, CAP_SET) != 0) {
        success = false;
    }
    
    if (success && cap_set_proc(caps) != 0) {
        success = false;
    }
    
    cap_free(caps);
    return success;
}

#else

bool drop_capability(Capability c) {
    (void)c;
    return false;
}

bool enable_effective_capability(Capability c) {
    (void)c;
    return false;
}

#endif  // HAVE_LIBCAP

// ============================================================================
// systemd Service Capability Configuration Parsing
// ============================================================================

static std::optional<std::string> read_file_contents(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

static std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    for (size_t i = 0; i <= str.length(); ++i) {
        if (i == str.length() || str[i] == delimiter) {
            std::string token = str.substr(start, i - start);
            size_t t_start = token.find_first_not_of(" \t\r\n");
            size_t t_end = token.find_last_not_of(" \t\r\n");
            if (t_start != std::string::npos) {
                token = token.substr(t_start, t_end - t_start + 1);
            }
            if (!token.empty()) {
                tokens.push_back(token);
            }
            start = i + 1;
        }
    }
    return tokens;
}

std::optional<SystemdServiceCapabilityConfig> parse_systemd_service_capabilities(
    const std::string& service_path) {
    
    auto content_opt = read_file_contents(service_path);
    if (!content_opt) {
        return std::nullopt;
    }
    
    SystemdServiceCapabilityConfig config;
    
    for (const auto& line : split_string(content_opt.value(), '\n')) {
        std::string line_stripped = line;
        
        size_t start = line_stripped.find_first_not_of(" \t");
        if (start != std::string::npos) {
            line_stripped = line_stripped.substr(start);
        } else {
            continue;
        }
        
        if (line_stripped.empty()) continue;
        
        if (starts_with(line_stripped, "CapabilityBoundingSet=")) {
            std::string caps_str = line_stripped.substr(22);
            for (const auto& cap_name : split_string(caps_str, ' ')) {
                if (!cap_name.empty()) {
                    auto opt_cap = from_string(cap_name.c_str());
                    if (opt_cap) {
                        config.bounding_set.insert(*opt_cap);
                    }
                }
            }
        } else if (starts_with(line_stripped, "AmbientCapabilities=")) {
            std::string caps_str = line_stripped.substr(20);
            for (const auto& cap_name : split_string(caps_str, ' ')) {
                if (!cap_name.empty()) {
                    auto opt_cap = from_string(cap_name.c_str());
                    if (opt_cap) {
                        config.ambient_caps.insert(*opt_cap);
                    }
                }
            }
        } else if (starts_with(line_stripped, "NoNewPrivileges=")) {
            std::string value = line_stripped.substr(16);
            config.no_new_privileges = (value == "true" || value == "1");
        } else if (starts_with(line_stripped, "DynamicUser=")) {
            std::string value = line_stripped.substr(12);
            config.dynamic_user = (value == "true" || value == "1");
        }
    }
    
    return config;
}

std::optional<SystemdServiceCapabilityConfig> get_systemd_service_capability_config(
    const std::string& service_name) {
    
    static constexpr const char* SERVICE_PATHS[] = {
        "/etc/systemd/system/",
        "/usr/lib/systemd/system/",
        "/run/systemd/system/",
    };
    
    for (const auto& path : SERVICE_PATHS) {
        std::string full_path = path + service_name;
        if (auto config = parse_systemd_service_capabilities(full_path)) {
            return config;
        }
        
        full_path += ".service";
        if (auto config = parse_systemd_service_capabilities(full_path)) {
            return config;
        }
    }
    
    return std::nullopt;
}

// ============================================================================
// Authorization Policy Integration
// ============================================================================

CapabilityAuthorizationDecision check_capability_authorization(
    const std::set<Capability>& required_caps) {
    
    CapabilityAuthorizationDecision decision;
    decision.required = required_caps;
    
    auto available = get_permitted_set();
    decision.available = available;
    
    bool all_present = true;
    for (auto c : required_caps) {
        // Get bounding bitmask and check if capability is present
        ProcessCapabilityState state = discover_capability_state();
        CapabilityBitmask bounding_mask = state.sets.bounding;
        if (!has_capability(bounding_mask, c)) {
            decision.decision = CapabilityAuthorizationDecision::Decision::kDeny;
            decision.reason = "capability not in bounding set";
            return decision;
        }
        if (!has_effective_capability(c)) {
            all_present = false;
        }
    }
    
    if (all_present) {
        decision.decision = CapabilityAuthorizationDecision::Decision::kAllow;
        decision.reason = "all required capabilities available and effective";
    } else {
        decision.decision = CapabilityAuthorizationDecision::Decision::kDeny;
        decision.reason = "required capability not currently active";
    }
    
    return decision;
}

CapabilityAuthorizationDecision check_service_authorization(
    const std::string& service_name,
    const std::set<Capability>& required_caps) {
    
    auto svc_config = get_systemd_service_capability_config(service_name);
    
    CapabilityAuthorizationDecision decision;
    decision.required = required_caps;
    
    if (!svc_config) {
        decision.available = get_permitted_set();
        decision.decision = CapabilityAuthorizationDecision::Decision::kInsufficientInformation;
        decision.reason = "could not read service configuration";
        return decision;
    }
    
    bool in_bounding_set = true;
    for (auto c : required_caps) {
        // Check if capability is in the service's bounding set
        CapabilityBitmask service_bounding = make_empty_bitmask();
        for (auto cap : svc_config->bounding_set) {
            set_capability(service_bounding, cap);
        }
        if (!has_capability(service_bounding, c)) {
            in_bounding_set = false;
            break;
        }
    }
    
    if (!in_bounding_set) {
        decision.available = get_permitted_set();
        decision.decision = CapabilityAuthorizationDecision::Decision::kDeny;
        decision.reason = "required capability not in service bounding set";
        return decision;
    }
    
    bool all_effective = true;
    for (auto c : required_caps) {
        if (!has_effective_capability(c)) {
            all_effective = false;
            break;
        }
    }
    
    if (all_effective) {
        decision.available = get_permitted_set();
        decision.decision = CapabilityAuthorizationDecision::Decision::kAllow;
        decision.reason = "service has all required capabilities";
    } else {
        decision.available = get_permitted_set();
        decision.decision = CapabilityAuthorizationDecision::Decision::kDeny;
        decision.reason = "required capability not currently effective";
    }
    
    return decision;
}

}  // namespace rebuntu::environment::capability_state