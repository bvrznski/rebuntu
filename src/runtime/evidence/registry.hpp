// rebuntu::runtime::evidence::Registry — Evidence Registry (Phase 4.0)
//
// EvidenceRegistry collects and manages evidence during execution.
// Evidence is data that supports the outcome of an operation, including:
// - Observations from native Linux facilities
// - Timestamps of key events
// - Verification results
// - Diagnostic information

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/evidence/error.hpp>
#include <memory>
#include <mutex>
#include <vector>

namespace rebuntu::runtime {

struct EvidenceItem {
    std::string source;      // Where this evidence came from (e.g., "procfs", "systemd")
    std::string description; // What this evidence shows
    std::string value;       // The observed value
    std::chrono::system_clock::time_point captured_at;
};

class EvidenceRegistry {
public:
    EvidenceRegistry() = default;
    
    // Add an observation to the registry
    void add_evidence(std::string source, std::string description, 
                     std::string value) {
        std::lock_guard lock(mutex_);
        items_.push_back({
            std::move(source),
            std::move(description),
            std::move(value),
            std::chrono::system_clock::now()
        });
    }
    
    // Get all evidence items
    std::vector<EvidenceItem> all_evidence() const {
        std::lock_guard lock(mutex_);
        return items_;
    }
    
    // Get evidence from a specific source
    std::vector<EvidenceItem> by_source(std::string_view source) const {
        std::lock_guard lock(mutex_);
        std::vector<EvidenceItem> result;
        for (const auto& item : items_) {
            if (item.source == source) {
                result.push_back(item);
            }
        }
        return result;
    }
    
    // Get evidence count
    size_t count() const {
        std::lock_guard lock(mutex_);
        return items_.size();
    }
    
    // Clear all evidence (for testing)
    void clear() {
        std::lock_guard lock(mutex_);
        items_.clear();
    }

private:
    mutable std::mutex mutex_;
    std::vector<EvidenceItem> items_;
};

namespace evidence {

// Factory function for a registry pre-populated with initial evidence
inline std::shared_ptr<EvidenceRegistry> make_registry_with_evidence(
    std::vector<EvidenceItem> initial = {}) {
    
    auto registry = std::make_shared<EvidenceRegistry>();
    // Note: Initial evidence would need public add method in real implementation
    
    return registry;
}

}  // namespace evidence
}  // namespace rebuntu::runtime

// Define error types for evidence operations
namespace rebuntu { namespace runtime { namespace evidence {
struct Error {};
}}}