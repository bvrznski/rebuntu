#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::proactive_operations::transactions::journal {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
