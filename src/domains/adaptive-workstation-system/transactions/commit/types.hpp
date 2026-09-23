#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::adaptive_workstation_system::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
