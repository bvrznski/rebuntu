#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_foundation::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
