#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::bounded_autonomous_operations::desired_state::model {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
