#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::core_runtime::scheduling::deadlines {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
