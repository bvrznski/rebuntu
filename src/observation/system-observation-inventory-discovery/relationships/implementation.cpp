// rebuntu::observation::system_observation_inventory_discovery::relationships
// — Relationship Evidence Provider Implementation (Phase 5.47)
//
// This module implements a relationship evidence provider that:
//   - Collects relationships from native Linux sources (procfs, sysfs)
//   - Tracks provenance for each observed relationship
//   - Does NOT infer causal relationships from topology or timing
//   - Reports only directly-observed relationships

#include "observation/system-observation-inventory-discovery/relationships/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

namespace rebuntu::observation::system_observation_inventory_discovery::relationships {

// ============================================================================
// ProcfsRelationshipEvidenceProvider — Implementation using procfs
//
// Collects relationships from /proc filesystem:
//   - Process-parent relationships (from /proc/[pid]/stat)
//   - Process-cgroup relationships (from /proc/[pid]/cgroup)
// ============================================================================
class ProcfsRelationshipEvidenceProvider : public RelationshipEvidenceProvider {
public:
    ProcfsRelationshipEvidenceProvider() = default;
    
    ~ProcfsRelationshipEvidenceProvider() override = default;
    
    // Query relationships for a specific entity
    RelationshipDiscoveryResult query(const EntityIdentity& entity) override {
        RelationshipDiscoveryResult result;
        
        if (entity.domain == "process") {
            result = query_process_relationships(entity);
        } else if (entity.domain == "cgroup") {
            result = query_cgroup_relationships(entity);
        }
        
        return result;
    }
    
    // Get all relationships
    RelationshipDiscoveryResult get_all_relationships() override {
        RelationshipDiscoveryResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Scan /proc for processes and collect their relationships
        collect_process_relationships(result);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        // Update statistics
        for (const auto& rel : result.relationships) {
            if (rel.relationship_type == RelationshipType::kBelongsTo) {
                result.by_type[0]++;  // kBelongsTo
            } else if (rel.relationship_type == RelationshipType::kParentOf) {
                result.by_type[6]++;  // kParentOf
            }
        }
        
        result.total_relationships = result.relationships.size();
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully discovered relationships from procfs";
        
        last_observation_time_ = result.observed_at;
        
        return result;
    }
    
    // Get relationships by type
    std::vector<RelationshipEvidence> get_by_type(RelationshipType type) override {
        std::vector<RelationshipEvidence> result;
        auto all = get_all_relationships();
        
        for (const auto& rel : all.relationships) {
            if (rel.relationship_type == type) {
                result.push_back(rel);
            }
        }
        
        return result;
    }
    
    // Get freshness
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }

private:
    std::chrono::system_clock::time_point last_observation_time_{};
    
    RelationshipDiscoveryResult query_process_relationships(const EntityIdentity& entity) {
        RelationshipDiscoveryResult result;
        
        // Parse PID from identifier (format: "pid@boot-timestamp")
        size_t at_pos = entity.identifier.find('@');
        if (at_pos == std::string::npos) {
            result.status = core::SemanticStatus::kFailure;
            result.description = "Invalid process identity format";
            return result;
        }
        
        std::string pid_str = entity.identifier.substr(0, at_pos);
        int pid = 0;
        try {
            pid = std::stoi(pid_str);
        } catch (...) {
            result.status = core::SemanticStatus::kFailure;
            result.description = "Invalid PID";
            return result;
        }
        
        std::string proc_path = "/proc/" + pid_str;
        
        // Collect process relationships from this specific process
        collect_process_relationships_for_pid(pid, proc_path, result);
        
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully queried process relationships";
        
        return result;
    }
    
    RelationshipDiscoveryResult query_cgroup_relationships(const EntityIdentity& entity) {
        // For now, return empty - cgroup membership is determined from processes
        RelationshipDiscoveryResult result;
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Cgroup relationships queried (reverse lookup not implemented)";
        return result;
    }
    
    void collect_cgroup_relationships(RelationshipDiscoveryResult& result) {
        // Cgroup membership is discovered from process observations
        // This function would need sysfs scanning for direct cgroup hierarchy
    }

    void collect_process_relationships(RelationshipDiscoveryResult& result) {
        DIR* proc_dir = opendir("/proc");
        if (!proc_dir) {
            result.status = core::SemanticStatus::kFailure;
            result.description = "Failed to open /proc directory";
            return;
        }
        
        struct dirent* entry;
        while ((entry = readdir(proc_dir)) != nullptr) {
            std::string name = entry->d_name;
            
            // Check if it's a numeric PID
            bool is_pid = !name.empty() && 
                std::all_of(name.begin(), name.end(), 
                    [](char c) { return std::isdigit(static_cast<unsigned char>(c)); });
            
            if (is_pid) {
                int pid = std::stoi(name);
                std::string proc_path = "/proc/" + name;
                
                collect_process_relationships_for_pid(pid, proc_path, result);
            }
        }
        
        closedir(proc_dir);
    }
    
    void collect_process_relationships_for_pid(int pid, const std::string& proc_path, 
                                                RelationshipDiscoveryResult& result) {
        // Collect parent relationship from /proc/[pid]/stat
        collect_parent_relationship(pid, proc_path, result);
        
        // Collect cgroup relationships from /proc/[pid]/cgroup
        collect_cgroup_relationships_for_pid(pid, proc_path, result);
    }
    
    void collect_parent_relationship(int pid, const std::string& proc_path,
                                     RelationshipDiscoveryResult& result) {
        std::string stat_path = proc_path + "/stat";
        std::ifstream file(stat_path);
        
        if (!file.is_open()) {
            // Process may have terminated - this is UNKNOWN, not absence
            return;
        }
        
        // Read the line and parse ppid (field 4 in /proc/[pid]/stat)
        std::string line;
        if (std::getline(file, line)) {
            // Parse stat fields: pid (comm) state ppid ...
            size_t open_paren = line.find('(');
            size_t close_paren = line.rfind(')');
            
            if (open_paren != std::string::npos && close_paren != std::string::npos) {
                std::string prefix = line.substr(0, open_paren);
                
                // Split and get ppid (field 4)
                std::istringstream iss(prefix);
                std::vector<std::string> fields;
                std::string field;
                while (iss >> field) {
                    fields.push_back(field);
                }
                
                if (fields.size() >= 4) {
                    try {
                        int ppid = std::stoi(fields[3]);
                        
                        if (ppid > 0) {
                            // Record the parent relationship
                            RelationshipEvidence evidence;
                            evidence.source.domain = "process";
                            evidence.source.identifier = std::to_string(pid);
                            evidence.target.domain = "process";
                            evidence.target.identifier = std::to_string(ppid);
                            evidence.relationship_type = RelationshipType::kParentOf;
                            
                            evidence.evidence_source.source_type = "procfs";
                            evidence.evidence_source.path = stat_path;
                            evidence.observed_at = std::chrono::system_clock::now();
                            
                            // Uncertainty: we don't know if the ppid is still valid
                            // (process may have terminated between reading parent and child)
                            evidence.uncertainty = RelationshipEvidence::UncertaintyLevel::kBounded;
                            evidence.uncertainty_reason = "Parent PID may have been reused";
                            
                            result.relationships.push_back(evidence);
                        }
                    } catch (...) {
                        // Could not parse ppid - record as partial evidence
                        RelationshipEvidence evidence;
                        evidence.source.domain = "process";
                        evidence.source.identifier = std::to_string(pid);
                        evidence.target.domain = "unknown";
                        evidence.target.identifier = "";
                        evidence.relationship_type = RelationshipType::kParentOf;
                        
                        evidence.evidence_source.source_type = "procfs";
                        evidence.evidence_source.path = stat_path;
                        evidence.observed_at = std::chrono::system_clock::now();
                        evidence.uncertainty = RelationshipEvidence::UncertaintyLevel::kUnknown;
                        evidence.uncertainty_reason = "Could not parse parent PID from /proc/[pid]/stat";
                        
                        result.relationships.push_back(evidence);
                    }
                }
            }
        }
    }
    
    void collect_cgroup_relationships_for_pid(int pid, const std::string& proc_path,
                                               RelationshipDiscoveryResult& result) {
        std::string cgroup_path = proc_path + "/cgroup";
        std::ifstream file(cgroup_path);
        
        if (!file.is_open()) {
            return;  // Process may have terminated
        }
        
        std::string line;
        while (std::getline(file, line)) {
            // Format: hierarchyID:cgroups_mask:path (e.g., "10:memory:/user.slice/user-1000")
            if (line.empty()) continue;
            
            size_t first_colon = line.find(':');
            size_t second_colon = line.find(':', first_colon + 1);
            
            if (second_colon != std::string::npos) {
                std::string cgroup_path_in_cgroup = line.substr(second_colon + 1);
                
                // Create a stable identifier for this cgroup
                std::string cgroup_id;
                if (!cgroup_path_in_cgroup.empty() && cgroup_path_in_cgroup[0] != '/') {
                    cgroup_id = "/" + cgroup_path_in_cgroup;
                } else {
                    cgroup_id = cgroup_path_in_cgroup;
                }
                
                // Record the belongs-to relationship
                RelationshipEvidence evidence;
                evidence.source.domain = "process";
                evidence.source.identifier = std::to_string(pid);
                evidence.target.domain = "cgroup";
                evidence.target.identifier = cgroup_id;
                evidence.relationship_type = RelationshipType::kBelongsTo;
                
                evidence.evidence_source.source_type = "procfs";
                evidence.evidence_source.path = cgroup_path;
                evidence.observed_at = std::chrono::system_clock::now();
                evidence.uncertainty = RelationshipEvidence::UncertaintyLevel::kNone;
                
                result.relationships.push_back(evidence);
            }
        }
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<RelationshipEvidenceProvider> make_relationship_evidence_provider() {
    return std::make_unique<ProcfsRelationshipEvidenceProvider>();
}

}  // namespace rebuntu::observation::system_observation_inventory_discovery::relationships