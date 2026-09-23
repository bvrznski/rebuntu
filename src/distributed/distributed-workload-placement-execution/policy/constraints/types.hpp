#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_workload_placement_execution::policy::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
