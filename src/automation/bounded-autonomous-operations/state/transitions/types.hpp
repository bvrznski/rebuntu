#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::bounded_autonomous_operations::state::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
