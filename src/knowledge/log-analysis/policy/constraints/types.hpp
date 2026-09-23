#pragma once
#include <string>
#include <vector>
namespace rebuntu::knowledge::log_analysis::policy::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
