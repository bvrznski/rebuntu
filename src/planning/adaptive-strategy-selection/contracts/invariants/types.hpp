#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::adaptive_strategy_selection::contracts::invariants {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
