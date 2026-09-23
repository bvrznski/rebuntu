#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::state::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
