#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
