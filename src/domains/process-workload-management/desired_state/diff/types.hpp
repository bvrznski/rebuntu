#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::process_workload_management::desired_state::diff {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
