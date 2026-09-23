#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::predictive_maintenance_failure_prevention::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
