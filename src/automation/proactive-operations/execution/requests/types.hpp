#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::proactive_operations::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
