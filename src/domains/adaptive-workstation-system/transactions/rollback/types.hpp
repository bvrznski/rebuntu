#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::adaptive_workstation_system::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
