#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::transactional_change_safe_transition::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
