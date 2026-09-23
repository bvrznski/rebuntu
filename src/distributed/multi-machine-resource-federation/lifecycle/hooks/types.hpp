#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::multi_machine_resource_federation::lifecycle::hooks {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
