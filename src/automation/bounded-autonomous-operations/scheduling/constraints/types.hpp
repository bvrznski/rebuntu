#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::bounded_autonomous_operations::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
