#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
