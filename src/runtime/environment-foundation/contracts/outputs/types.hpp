#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_foundation::contracts::outputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
