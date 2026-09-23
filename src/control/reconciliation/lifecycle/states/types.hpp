#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::lifecycle::states {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
