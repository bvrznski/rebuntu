#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::proactive_operations::operations::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
