#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::transactional_change_safe_transition::state::persistence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
