#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::terminal_management::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
