#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::automation_workflow_system::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
