#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
