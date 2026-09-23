#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
