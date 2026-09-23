#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::adaptive_strategy_selection::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
