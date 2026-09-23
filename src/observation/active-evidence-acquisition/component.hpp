#pragma once

#include <string_view>

namespace rebuntu::observation::active_evidence_acquisition {

// Structural integration point for active evidence acquisition.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ActiveEvidenceAcquisitionComponent {
public:
    virtual ~ActiveEvidenceAcquisitionComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "active-evidence-acquisition"; }
};

} // namespace rebuntu::observation::active_evidence_acquisition
