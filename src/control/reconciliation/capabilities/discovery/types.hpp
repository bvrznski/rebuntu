#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::capabilities::discovery {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
