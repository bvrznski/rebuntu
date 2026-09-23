#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::unified_control_plane::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
