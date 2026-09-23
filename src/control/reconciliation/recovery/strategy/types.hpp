#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
