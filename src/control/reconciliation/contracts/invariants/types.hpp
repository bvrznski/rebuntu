#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::contracts::invariants {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
