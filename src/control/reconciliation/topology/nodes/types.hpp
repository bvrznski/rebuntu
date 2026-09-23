#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::topology::nodes {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
