#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::model::identifiers {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
