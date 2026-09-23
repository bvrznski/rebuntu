#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::automation_workflow_system::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
