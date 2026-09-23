#pragma once
#include <string>
#include <vector>
namespace rebuntu::knowledge::log_analysis::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
