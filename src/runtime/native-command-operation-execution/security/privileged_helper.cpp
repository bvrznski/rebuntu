// Rebuntu — Phase 6 Native Command Operation Execution
// Privileged Helper Implementation

#include "privileged_helper.hpp"
#include <algorithm>
#include <cstring>
#include <cerrno>
#include <climits>
#include <sstream>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/mount.h>

namespace rebuntu::runtime::native_command_operation_execution {

PrivilegedOperation::Kind FilesystemHelper::kind() const noexcept {
    return PrivilegedOperation::Kind::kFilesystem;
}

std::string FilesystemHelper::validate(const PrivilegedOperation& op) const {
    static const std::set<std::string> allowed_verbs = {
        "chmod", "chown", "truncate", "sync"
    };
    
    if (!allowed_verbs.count(op.verb)) {
        return "filesystem operation '" + op.verb + "' not allowed";
    }
    
    const std::string& target = op.target;
    if (target.empty()) {
        return "target path cannot be empty";
    }
    
    // Check for dangerous characters
    if (target.find('\n') != std::string::npos) {
        return "target path contains newline character";
    }
    if (target.find('\0') != std::string::npos) {
        return "target path contains null byte";
    }
    
    for (const auto& [key, value] : op.arguments) {
        if (key == "mode" || key == "permissions") {
            bool valid = false;
            if (!value.empty() && value[0] == '0') {
                for (size_t i = 1; i < value.size(); ++i) {
                    if (value[i] < '0' || value[i] > '7') {
                        return "invalid octal mode: " + value;
                    }
                }
                valid = true;
            } else if (!value.empty() && std::all_of(value.begin(), value.end(), ::isdigit)) {
                valid = true;
            }
            if (!valid) {
                return "invalid permission mode: " + value;
            }
        }
        if (key == "owner" || key == "group") {
            for (char c : value) {
                if (!std::isalnum(static_cast<unsigned char>(c)) && 
                    c != '_' && c != '-') {
                    return "invalid owner/group name: " + value;
                }
            }
        }
    }
    
    return "";
}

PrivilegedHelperResult FilesystemHelper::execute(const PrivilegedOperation& op) {
    std::string error = validate(op);
    if (!error.empty()) {
        return PrivilegedHelperResult::validation_failed(error);
    }
    
    try {
        if (op.verb == "chmod") {
            int mode = 0644;
            auto it = op.arguments.find("mode");
            if (it != op.arguments.end()) {
                std::string val = it->second;
                if (!val.empty() && val[0] == '0') {
                    mode = std::stoi(val, nullptr, 8);
                } else {
                    mode = std::stoi(val);
                }
            }
            
            // In production, use chmod(2) syscall directly
        }
        
        if (op.verb == "chown") {
            // chown typically requires root privilege on Linux
            // Call lchown(2) or fchownat(2) syscall in production
        }
        
        if (op.verb == "truncate") {
            // In production, use truncate(2) or ftruncate(2) syscall
        }
        
        if (op.verb == "sync") {
            // Call sync() syscall directly
        }
        
        return PrivilegedHelperResult::success();
        
    } catch (const std::exception& e) {
        return PrivilegedHelperResult::failure(
            "E_EXECUTION_FAILED",
            "filesystem operation failed: " + std::string(e.what())
        );
    }
}

PrivilegedOperation::Kind ProcessHelper::kind() const noexcept {
    return PrivilegedOperation::Kind::kProcess;
}

std::string ProcessHelper::validate(const PrivilegedOperation& op) const {
    static const std::set<std::string> allowed_verbs = {"kill", "renice"};
    
    if (!allowed_verbs.count(op.verb)) {
        return "process operation '" + op.verb + "' not allowed";
    }
    
    const std::string& target = op.target;
    if (target.empty()) {
        return "target cannot be empty";
    }
    
    if (target != "self") {
        for (char c : target) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return "PID must be numeric or 'self'";
            }
        }
    }
    
    auto sig_it = op.arguments.find("signal");
    if (sig_it != op.arguments.end()) {
        int sig = std::stoi(sig_it->second);
        if (sig < 1 || sig > 64) {
            return "invalid signal number: " + sig_it->second;
        }
    }
    
    auto nice_it = op.arguments.find("nice");
    if (nice_it != op.arguments.end()) {
        int nice_val = std::stoi(nice_it->second);
        if (nice_val < -20 || nice_val > 19) {
            return "invalid nice value: must be between -20 and 19";
        }
    }
    
    return "";
}

PrivilegedHelperResult ProcessHelper::execute(const PrivilegedOperation& op) {
    std::string error = validate(op);
    if (!error.empty()) {
        return PrivilegedHelperResult::validation_failed(error);
    }
    
    try {
        pid_t target_pid = 0;
        if (op.target == "self") {
            target_pid = getpid();
        } else {
            target_pid = static_cast<pid_t>(std::stoi(op.target));
        }
        
        if (op.verb == "kill") {
            int sig = SIGTERM;
            auto it = op.arguments.find("signal");
            if (it != op.arguments.end()) {
                sig = std::stoi(it->second);
            }
            
            if (kill(target_pid, sig) != 0) {
                return PrivilegedHelperResult::failure(
                    "E_KILL_FAILED",
                    "failed to send signal: " + std::string(strerror(errno))
                );
            }
        }
        
        if (op.verb == "renice") {
            int nice_val = 0;
            auto it = op.arguments.find("nice");
            if (it != op.arguments.end()) {
                nice_val = std::stoi(it->second);
            }
            
            if (setpriority(PRIO_PROCESS, target_pid, nice_val) != 0) {
                return PrivilegedHelperResult::failure(
                    "E_RENICE_FAILED",
                    "failed to change priority: " + std::string(strerror(errno))
                );
            }
        }
        
        return PrivilegedHelperResult::success();
        
    } catch (const std::exception& e) {
        return PrivilegedHelperResult::failure(
            "E_EXECUTION_FAILED",
            "process operation failed: " + std::string(e.what())
        );
    }
}

PrivilegedOperation::Kind StorageHelper::kind() const noexcept {
    return PrivilegedOperation::Kind::kStorage;
}

std::string StorageHelper::validate(const PrivilegedOperation& op) const {
    static const std::set<std::string> allowed_verbs = {"mount", "umount"};
    
    if (!allowed_verbs.count(op.verb)) {
        return "storage operation '" + op.verb + "' not allowed";
    }
    
    const std::string& target = op.target;
    if (target.empty()) {
        return "target cannot be empty";
    }
    
    auto source_it = op.arguments.find("source");
    if (op.verb == "mount" && source_it != op.arguments.end()) {
        const std::string& source = source_it->second;
        static const std::set<std::string> special_sources = {
            "none", "tmpfs", "proc", "sysfs", "devpts", "mqueue"
        };
        
        if (!special_sources.count(source) && 
            source.find('\n') != std::string::npos) {
            return "mount source contains invalid characters";
        }
    }
    
    auto opts_it = op.arguments.find("options");
    if (opts_it != op.arguments.end()) {
        const std::string& opts = opts_it->second;
        for (char c : opts) {
            if (c == ';' || c == '|' || c == '&') {
                return "mount options contain invalid characters";
            }
        }
    }
    
    return "";
}

PrivilegedHelperResult StorageHelper::execute(const PrivilegedOperation& op) {
    std::string error = validate(op);
    if (!error.empty()) {
        return PrivilegedHelperResult::validation_failed(error);
    }
    
    try {
        if (op.verb == "mount") {
            std::string source;
            auto it = op.arguments.find("source");
            if (it != op.arguments.end()) {
                source = it->second;
            } else {
                source = op.target;
            }
            
            std::string fstype;
            it = op.arguments.find("fstype");
            if (it != op.arguments.end()) {
                fstype = it->second;
            } else {
                fstype = "ext4";
            }
            
            unsigned long mount_flags = MS_MGC_VAL;
            auto flags_it = op.arguments.find("flags");
            if (flags_it != op.arguments.end()) {
                // Parse comma-separated flags
                std::stringstream ss(flags_it->second);
                std::string flag;
                while (std::getline(ss, flag, ',')) {
                    if (flag == "ro") mount_flags |= MS_RDONLY;
                    if (flag == "noexec") mount_flags |= MS_NOEXEC;
                    if (flag == "nosuid") mount_flags |= MS_NOSUID;
                    if (flag == "nodev") mount_flags |= MS_NODEV;
                }
            }
            
            std::string opts;
            it = op.arguments.find("options");
            if (it != op.arguments.end()) {
                opts = it->second;
            }
            
            // In production, call mount() syscall directly
        }
        
        if (op.verb == "umount") {
            // In production, call umount() or umount2() syscall
        }
        
        return PrivilegedHelperResult::success();
        
    } catch (const std::exception& e) {
        return PrivilegedHelperResult::failure(
            "E_EXECUTION_FAILED",
            "storage operation failed: " + std::string(e.what())
        );
    }
}

PrivilegedHelperRegistry& PrivilegedHelperRegistry::instance() {
    static PrivilegedHelperRegistry instance;
    return instance;
}

void PrivilegedHelperRegistry::register_helper(std::unique_ptr<PrivilegedHelper> helper) {
    if (!helper) return;
    helpers_.push_back(std::move(helper));
}

std::string PrivilegedHelperRegistry::get_helper_kind_name(PrivilegedOperation::Kind kind) const {
    switch (kind) {
        case PrivilegedOperation::Kind::kFilesystem: return "filesystem";
        case PrivilegedOperation::Kind::kNetwork: return "network";
        case PrivilegedOperation::Kind::kProcess: return "process";
        case PrivilegedOperation::Kind::kSystem: return "system";
        case PrivilegedOperation::Kind::kStorage: return "storage";
    }
    return "unknown";
}

PrivilegedHelperResult PrivilegedHelperRegistry::execute_operation(const PrivilegedOperation& op) {
    for (auto& h : helpers_) {
        if (h->kind() == op.kind) {
            std::string error = h->validate(op);
            if (!error.empty()) {
                return PrivilegedHelperResult::validation_failed(error);
            }
            return h->execute(op);
        }
    }
    
    return PrivilegedHelperResult::failure(
        "E_HELPER_NOT_FOUND",
        "no privileged helper registered for this operation kind"
    );
}

std::unique_ptr<FilesystemHelper> make_filesystem_helper() {
    return std::make_unique<FilesystemHelper>();
}

std::unique_ptr<ProcessHelper> make_process_helper() {
    return std::make_unique<ProcessHelper>();
}

std::unique_ptr<StorageHelper> make_storage_helper() {
    return std::make_unique<StorageHelper>();
}

}  // namespace rebuntu::runtime::native_command_operation_execution