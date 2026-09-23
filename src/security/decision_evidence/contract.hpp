#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::security::decision_evidence {
struct DecisionEvidenceContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
