#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::verification::reports {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
