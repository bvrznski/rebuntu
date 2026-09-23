#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::development_environment_management::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
