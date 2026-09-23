#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::recovery::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
