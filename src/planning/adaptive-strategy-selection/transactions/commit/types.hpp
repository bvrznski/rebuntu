#pragma once
#include <string>
#include <vector>
namespace rebuntu::planning::adaptive_strategy_selection::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
