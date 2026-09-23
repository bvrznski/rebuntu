#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::proactive_operations::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
