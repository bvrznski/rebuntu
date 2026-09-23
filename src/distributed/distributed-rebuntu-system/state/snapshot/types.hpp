#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_rebuntu_system::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
