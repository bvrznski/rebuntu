#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::shell_management::authorization::permissions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
