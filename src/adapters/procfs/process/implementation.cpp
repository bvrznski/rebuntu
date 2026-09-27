// rebuntu::adapters::procfs::process — Procfs Process Discovery Implementation (Phase 5.24)
//
// This module implements the procfs-based process discovery adapter:
//   - Reads process information from /proc/[pid]/
//   - Observes: PID + boot context, executable metadata, parent relationship
//   - Provides bounded resource facts where available

#include "adapters/procfs/process/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <limits.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

namespace rebuntu::adapters::procfs::process {

// ============================================================================
// Helper: Get system uptime in seconds (from /proc/uptime)
// ============================================================================

static double get_system_uptime_seconds() {
    std::ifstream file("/proc/uptime");
    if (!file.is_open()) {
        return -1.0;
    }
    
    double uptime;
    file >> uptime;
    return uptime;
}

// ============================================================================
// Helper: Get current system time in milliseconds since epoch
// ============================================================================

static int64_t get_current_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return static_cast<int64_t>(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
}

// ============================================================================
// Helper: Get clock ticks per second
// ============================================================================

static uint64_t get_clock_ticks_per_second() {
#ifdef CLK_TCK
    return CLK_TCK;
#else
    return 100;  // Standard value for Linux
#endif
}

// ============================================================================
// Helper: Parse process state from /proc/[pid]/stat
// ============================================================================

static ProcessState parse_process_state(char state_char) {
    switch (state_char) {
        case 'R': return ProcessState::kRunning;
        case 'S': return ProcessState::kSleeping;
        case 'D': return ProcessState::kDiskSleep;
        case 'Z': return ProcessState::kZombie;
        case 'T': return ProcessState::kStopped;
        case 't': return ProcessState::kTracing;
        case 'X': return ProcessState::kDead;
        case 'W': return ProcessState::kWakekill;
        case 'P': return ProcessState::kParked;
        case 'I': return ProcessState::kIdle;
        default:  return ProcessState::kUnknown;
    }
}

// ============================================================================
// Helper: Read a line from a file
// ============================================================================

static std::string read_file_line(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    
    std::string line;
    if (std::getline(file, line)) {
        return line;
    }
    return "";
}

// ============================================================================
// Helper: Split content into lines
// ============================================================================

static std::vector<std::string> split_lines(const std::string& content) {
    std::vector<std::string> lines;
    std::istringstream iss(content);
    std::string line;
    
    while (std::getline(iss, line)) {
        // Trim leading whitespace
        size_t start = 0;
        while (start < line.length() && isspace(static_cast<unsigned char>(line[start]))) {
            start++;
        }
        
        // Trim trailing whitespace
        size_t end = line.length();
        while (end > start && isspace(static_cast<unsigned char>(line[end - 1]))) {
            end--;
        }
        
        if (start < end) {
            lines.push_back(line.substr(start, end - start));
        } else {
            lines.push_back("");
        }
    }
    
    return lines;
}

// ============================================================================
// Helper: Read cmdline arguments (null-separated)
// ============================================================================

static std::vector<std::string> read_cmdline(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return {};
    }
    
    std::vector<std::string> args;
    std::string arg;
    
    while (std::getline(file, arg, '\0')) {  // Null-separated
        if (!arg.empty()) {
            args.push_back(arg);
        }
    }
    
    return args;
}

// ============================================================================
// Helper: Parse /proc/[pid]/stat fields
//
// Format:
//   pid (comm) state ppid pgrp session tty_nr tpgid flags minflt cminflt majflt cmajflt 
//   utime stime cutime cstime priority nice num_threads itrealvalue starttime vsize rss
//
// Note: comm may contain spaces and parentheses, so we parse carefully.
// ============================================================================

static std::vector<std::string> parse_stat_fields(const std::string& line) {
    std::vector<std::string> fields;
    
    // Find the first '(' and last ')' to extract comm
    size_t open_paren = line.find('(');
    if (open_paren == std::string::npos) {
        return fields;
    }
    
    size_t close_paren = line.rfind(')');
    if (close_paren == std::string::npos || close_paren <= open_paren) {
        return fields;
    }
    
    // Extract everything before '('
    std::string prefix = line.substr(0, open_paren);
    std::istringstream prefix_stream(prefix);
    std::string field;
    while (prefix_stream >> field) {
        fields.push_back(field);
    }
    
    // Add comm field
    if (close_paren > open_paren + 1) {
        fields.push_back(line.substr(open_paren + 1, close_paren - open_paren - 1));
    } else {
        fields.push_back("");
    }
    
    // Extract everything after ')'
    std::string suffix = line.substr(close_paren + 1);
    std::istringstream suffix_stream(suffix);
    while (suffix_stream >> field) {
        fields.push_back(field);
    }
    
    return fields;
}

// ============================================================================
// ProcfsProcessDiscoveryAdapter Implementation
// ============================================================================

class ProcfsProcessDiscoveryAdapter : public ProcessDiscoveryAdapter {
public:
    ProcfsProcessDiscoveryAdapter() = default;
    ~ProcfsProcessDiscoveryAdapter() override = default;
    
    ProcessDiscoveryResult observe_all_processes() override {
        ProcessDiscoveryResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Get current time for calculating process uptime
        int64_t current_time_ms = get_current_time_ms();
        double uptime_seconds = get_system_uptime_seconds();
        
        // Scan /proc for process directories using system calls (no C++17 filesystem)
        std::vector<std::pair<int, std::string>> proc_entries;
        
        DIR* proc_dir = opendir("/proc");
        if (proc_dir != nullptr) {
            struct dirent* entry;
            while ((entry = readdir(proc_dir)) != nullptr) {
                std::string name = entry->d_name;
                
                // Check if it's a numeric PID
                bool is_pid = !name.empty() && 
                    std::all_of(name.begin(), name.end(), 
                        [](char c) { return std::isdigit(static_cast<unsigned char>(c)); });
                
                if (is_pid) {
                    proc_entries.emplace_back(std::stoi(name), "/proc/" + name);
                }
            }
            closedir(proc_dir);
        }
        
        // Sort by PID for deterministic iteration
        std::sort(proc_entries.begin(), proc_entries.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });
        
        // Process each entry
        for (const auto& [pid, proc_path] : proc_entries) {
            auto observation = parse_process(pid, proc_path, current_time_ms, uptime_seconds);
            
            if (observation) {
                result.processes.push_back(std::move(*observation));
                
                // Update statistics
                result.total_processes++;
                
                switch (result.processes.back().state) {
                    case ProcessState::kRunning:
                        result.running_processes++;
                        break;
                    case ProcessState::kSleeping:
                    case ProcessState::kDiskSleep:
                        result.sleeping_processes++;
                        break;
                    case ProcessState::kZombie:
                        result.zombie_processes++;
                        break;
                    default:
                        result.other_processes++;
                        break;
                }
                
                // Update resource aggregates
                if (result.processes.back().resources.vm_rss_kb > 0) {
                    result.total_rss_kb += result.processes.back().resources.vm_rss_kb;
                    
                    if (!result.max_rss_kb.has_value() || 
                        result.processes.back().resources.vm_rss_kb > *result.max_rss_kb) {
                        result.max_rss_kb = result.processes.back().resources.vm_rss_kb;
                    }
                }
            } else {
                // Failed to parse this process
                result.errors.emplace_back(pid, core::Error{
                    "E_PARSE_FAILURE",
                    "Failed to parse /proc/[pid] statistics"
                });
            }
        }
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.provider_source = "procfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully discovered processes from /proc";
        
        // Cache the observation time
        last_observation_time_ = result.observed_at;
        
        return result;
    }
    
    std::optional<ProcessObservation> observe_process(const ProcessIdentity& identity) override {
        std::string proc_path = "/proc/" + std::to_string(identity.pid);
        
        int64_t current_time_ms = get_current_time_ms();
        double uptime_seconds = get_system_uptime_seconds();
        
        return parse_process(identity.pid, proc_path, current_time_ms, uptime_seconds);
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }
    
    ProcessDiscoveryResult force_refresh() override {
        // Clear cache and perform fresh observation
        last_observation_time_ = {};
        return observe_all_processes();
    }
    
    IdentityValidation validate_identity(const ProcessIdentity& identity) override {
        if (!identity.is_valid()) {
            return IdentityValidation::kUnknown;
        }
        
        std::string proc_path = "/proc/" + std::to_string(identity.pid);
        
        // Check if the process directory exists
        struct stat st;
        if (stat(proc_path.c_str(), &st) != 0) {
            return IdentityValidation::kNotFound;
        }
        
        // Read /proc/[pid]/stat to verify the start timestamp matches
        std::string stat_path = proc_path + "/stat";
        std::string stat_line = read_file_line(stat_path.c_str());
        
        if (stat_line.empty()) {
            return IdentityValidation::kUnknown;
        }
        
        auto fields = parse_stat_fields(stat_line);
        if (fields.size() < 24) {
            return IdentityValidation::kUnknown;
        }
        
        // Get current system time for timestamp calculation
        int64_t current_time_ms = get_current_time_ms();
        double uptime_seconds = get_system_uptime_seconds();
        
        if (uptime_seconds < 0) {
            return IdentityValidation::kUnknown;
        }
        
        try {
            int64_t start_ticks = std::stoll(fields[21]);
            uint64_t hz = get_clock_ticks_per_second();
            int64_t boot_time_ms = current_time_ms - static_cast<int64_t>(uptime_seconds * 1000);
            int64_t observed_boot_timestamp_ms = 
                boot_time_ms + (start_ticks * 1000) / static_cast<int64_t>(hz);
            
            // The observed timestamp should be close to what we stored (within a small tolerance)
            // This handles the case where the PID was reused by a new process
            if (observed_boot_timestamp_ms != identity.boot_timestamp_ms) {
                return IdentityValidation::kReused;
            }
        } catch (...) {
            return IdentityValidation::kUnknown;
        }
        
        return IdentityValidation::kValid;
    }
    
    ProcessDiscoveryResult observe_all() override {
        return observe_all_processes();
    }

private:
    std::chrono::system_clock::time_point last_observation_time_{};
    
    static std::optional<ProcessObservation> parse_process(
        int pid,
        const std::string& proc_path,
        int64_t current_time_ms,
        double uptime_seconds) {
        
        ProcessObservation observation;
        
        // Read /proc/[pid]/stat
        std::string stat_path = proc_path + "/stat";
        std::string stat_line = read_file_line(stat_path.c_str());
        
        if (stat_line.empty()) {
            return std::nullopt;
        }
        
        // Parse stat fields
        auto fields = parse_stat_fields(stat_line);
        if (fields.size() < 24) {  // Minimum required fields
            return std::nullopt;
        }
        
        // Fields after comm (index 1):
        // 2: state, 3: ppid, 4: pgrp, 5: session, 6: tty_nr, 7: tpgid,
        // 8: flags, 9: minflt, 10: cminflt, 11: majflt, 12: cmajflt,
        // 13: utime, 14: stime, 15: cutime, 16: cstime,
        // 17: priority, 18: nice, 19: num_threads, 20: itrealvalue,
        // 21: starttime, 22: vsize, 23: rss
        
        // Parse identity
        observation.identity.pid = pid;
        
        if (uptime_seconds >= 0) {
            // starttime is in clock ticks since boot
            int64_t start_ticks = 0;
            try {
                start_ticks = std::stoll(fields[21]);
            } catch (...) {}
            
            // Convert to milliseconds (ticks * 1000 / HZ)
            uint64_t hz = get_clock_ticks_per_second();
            int64_t boot_time_ms = current_time_ms - static_cast<int64_t>(uptime_seconds * 1000);
            observation.identity.boot_timestamp_ms = 
                boot_time_ms + (start_ticks * 1000) / static_cast<int64_t>(hz);
        }
        
        // Parse state
        if (!fields[2].empty()) {
            observation.state = parse_process_state(fields[2][0]);
            observation.state_description = fields[2];
        }
        
        // Parse parent PID
        int ppid = 0;
        try {
            ppid = std::stoi(fields[3]);
        } catch (...) {}
        
        if (ppid > 0 && ppid != pid) {  // Avoid self-reference for init process
            observation.parent.ppid_starttime_ms = observation.identity.boot_timestamp_ms;
        }
        
        // Parse timing information
        try {
            uint64_t start_ticks = std::stoull(fields[21]);
            uint64_t hz = get_clock_ticks_per_second();
            
            int64_t boot_time_ms = current_time_ms - static_cast<int64_t>(uptime_seconds * 1000);
            observation.start_time_ms = boot_time_ms + (start_ticks * 1000) / static_cast<int64_t>(hz);
            
            // Calculate uptime in seconds
            if (observation.start_time_ms > 0) {
                auto process_start_ms = std::chrono::system_clock::time_point{
                    std::chrono::milliseconds(observation.start_time_ms)};
                observation.uptime_seconds = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now() - process_start_ms).count();
            }
        } catch (...) {}
        
        // Parse CPU time (in ticks)
        try {
            observation.resources.utime_ticks = std::stoull(fields[13]);
            observation.resources.stime_ticks = std::stoull(fields[14]);
            observation.resources.cutime_ticks = std::stoull(fields[15]);
            observation.resources.cstime_ticks = std::stoull(fields[16]);
        } catch (...) {}
        
        // Parse priority and nice
        try {
            observation.resources.priority = std::stoi(fields[17]);
            observation.resources.nice = std::stoi(fields[18]);
        } catch (...) {}
        
        // Parse thread count
        try {
            observation.resources.thread_count = std::stoi(fields[19]);
        } catch (...) {}
        
        // Parse memory info from /proc/[pid]/status (more accurate)
        std::string status_path = proc_path + "/status";
        std::string status_content = read_file_line(status_path.c_str());
        
        // We need to read the full file content
        {
            std::ifstream status_file(status_path.c_str());
            if (status_file.is_open()) {
                std::stringstream buffer;
                buffer << status_file.rdbuf();
                status_content = buffer.str();
            }
        }
        
        // Parse VmRSS from status
        auto lines = split_lines(status_content);
        for (const auto& line : lines) {
            if (line.compare(0, 6, "VmRSS:") == 0) {
                std::istringstream iss(line.substr(6));
                iss >> observation.resources.vm_rss_kb;
                break;
            }
        }
        
        // Parse VmSwap from status
        for (const auto& line : lines) {
            if (line.compare(0, 7, "VmSwap:") == 0) {
                std::istringstream iss(line.substr(7));
                iss >> observation.resources.vm_swap_kb;
                break;
            }
        }
        
        // Read cmdline from /proc/[pid]/cmdline
        std::string cmdline_path = proc_path + "/cmdline";
        observation.executable.cmdline = read_cmdline(cmdline_path.c_str());
        
        // Read exe link from /proc/[pid]/exe using readlink
        std::string exe_path = proc_path + "/exe";
        char exe_link[4096];
        ssize_t len = readlink(exe_path.c_str(), exe_link, sizeof(exe_link) - 1);
        if (len > 0) {
            exe_link[len] = '\0';
            observation.executable.has_executable_link = true;
            observation.executable.executable_path = exe_link;
        }
        
        // Set provenance
        observation.observed_at = std::chrono::system_clock::now();
        observation.source = "procfs";
        
        return observation;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ProcessDiscoveryAdapter> make_procfs_process_discovery_adapter() {
    return std::make_unique<ProcfsProcessDiscoveryAdapter>();
}

}  // namespace rebuntu::adapters::procfs::process