#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
