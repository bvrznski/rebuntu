#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::change_impact_consequence_analysis::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
