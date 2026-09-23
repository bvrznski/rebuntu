#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::execution::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
