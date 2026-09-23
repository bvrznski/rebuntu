#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::health::recovery {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
