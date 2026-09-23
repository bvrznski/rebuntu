#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::environment_foundation::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
