#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::active_evidence_acquisition::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
