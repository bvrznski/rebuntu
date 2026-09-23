#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::software_environment_evolution::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
