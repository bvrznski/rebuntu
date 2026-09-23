#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_workload_placement_execution::contracts::outputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
