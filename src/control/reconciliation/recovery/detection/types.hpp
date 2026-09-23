#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::recovery::detection {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
