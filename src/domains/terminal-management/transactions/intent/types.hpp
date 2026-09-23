#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::terminal_management::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
