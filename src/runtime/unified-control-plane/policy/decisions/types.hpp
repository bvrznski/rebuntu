#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::unified_control_plane::policy::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
