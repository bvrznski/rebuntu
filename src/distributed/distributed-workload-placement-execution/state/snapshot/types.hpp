#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_workload_placement_execution::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
