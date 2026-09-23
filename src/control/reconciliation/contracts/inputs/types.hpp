#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
