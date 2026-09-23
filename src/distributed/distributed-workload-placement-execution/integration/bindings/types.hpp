#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_workload_placement_execution::integration::bindings {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
