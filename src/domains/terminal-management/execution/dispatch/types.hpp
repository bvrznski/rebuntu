#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::terminal_management::execution::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
