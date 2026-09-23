#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::integration::bindings {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
