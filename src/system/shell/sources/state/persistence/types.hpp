#pragma once
#include <string>
#include <vector>
namespace rebuntu::system::shell::sources::state::persistence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
