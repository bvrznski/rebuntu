#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
