#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
