#pragma once
#include <chrono>
#include <string>
#include <vector>

namespace rebuntu::core {

// ============================================================================
// Evidence — Provenance-bearing observation supporting claims about system state
// ============================================================================

struct Evidence {
    std::string subject;                    // What the evidence is about (e.g., "supported-distribution")
    std::string source;                     // Where the data came from (/etc/os-release, geteuid(), etc.)
    std::chrono::system_clock::time_point observed_at;
    std::string value;                      // The observation result ("passed", "failed", version string, etc.)
};

// ============================================================================
// EvidenceStore — Container for evidence with query support
// ============================================================================

class EvidenceStore {
public:
    void append(Evidence e) { records_.push_back(std::move(e)); }
    
    const std::vector<Evidence>& records() const noexcept { return records_; }
    
    std::vector<Evidence> for_subject(const std::string& s) const {
        std::vector<Evidence> out;
        for (const auto& r : records_) {
            if (r.subject == s) {
                out.push_back(r);
            }
        }
        return out;
    }
    
    void clear() noexcept { records_.clear(); }

private:
    std::vector<Evidence> records_;
};

}  // namespace rebuntu::core
