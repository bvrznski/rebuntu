#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::process_workload_management::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
