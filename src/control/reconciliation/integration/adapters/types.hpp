#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::integration::adapters {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
