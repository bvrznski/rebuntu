#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::scheduling::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
