#pragma once
#include <string>
#include <vector>
namespace rebuntu::knowledge::root_cause_diagnostic_reasoning::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
