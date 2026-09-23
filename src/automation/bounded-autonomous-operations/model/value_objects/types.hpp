#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::bounded_autonomous_operations::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
