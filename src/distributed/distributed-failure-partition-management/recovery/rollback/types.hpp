#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_failure_partition_management::recovery::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
