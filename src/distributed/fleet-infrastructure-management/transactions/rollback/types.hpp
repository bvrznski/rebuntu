#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::fleet_infrastructure_management::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
