#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::fleet_infrastructure_management::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
