#pragma once
#include <string>
#include <vector>
namespace rebuntu::knowledge::log_analysis::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
