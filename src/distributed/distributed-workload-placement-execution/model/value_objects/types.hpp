#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_workload_placement_execution::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
