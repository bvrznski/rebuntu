#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::adaptive_strategy_selection::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
