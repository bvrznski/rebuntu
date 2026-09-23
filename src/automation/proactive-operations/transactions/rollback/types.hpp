#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::proactive_operations::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
