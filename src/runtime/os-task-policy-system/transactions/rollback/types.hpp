#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::os_task_policy_system::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
