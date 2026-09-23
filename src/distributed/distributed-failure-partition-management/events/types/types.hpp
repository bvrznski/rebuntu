#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_failure_partition_management::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
