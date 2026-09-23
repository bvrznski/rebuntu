#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::fleet_infrastructure_management::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
