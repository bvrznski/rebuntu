#pragma once
#include <string>
#include <vector>
namespace rebuntu::knowledge::causal_system_analysis::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
