#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::shell_management::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
