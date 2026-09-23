#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::integration::bindings {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
