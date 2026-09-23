#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::transactional_change_safe_transition::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
