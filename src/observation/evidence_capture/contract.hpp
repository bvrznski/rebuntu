#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::observation::evidence_capture {
struct EvidenceCaptureContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
