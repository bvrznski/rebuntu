#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
