#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::state::history {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
