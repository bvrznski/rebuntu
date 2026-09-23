#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::core_runtime::policy::rules {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
