// rebuntu::system::diagnostics::snapshot — Evidence utilities for snapshot service (Phase 5.13)

#pragma once

#include "types.hpp"

namespace rebuntu::system::diagnostics::snapshot {

// Evidence quality indicators
enum class EvidenceQuality {
    kDirect,        // Direct observation from native source
    kDeduced,       // Deterministic deduction from observations
    kCorrelated,    // Correlation with other events (caution: not causation)
};

inline std::string to_string(EvidenceQuality q) {
    switch (q) {
        case EvidenceQuality::kDirect:     return "direct";
        case EvidenceQuality::kDeduced:    return "deduced";
        case EvidenceQuality::kCorrelated: return "correlated";
    }
    return "unknown";
}

}  // namespace rebuntu::system::diagnostics::snapshot