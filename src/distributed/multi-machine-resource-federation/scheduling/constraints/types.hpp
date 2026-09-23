#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::multi_machine_resource_federation::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
