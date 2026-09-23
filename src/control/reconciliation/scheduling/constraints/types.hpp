#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
