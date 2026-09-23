#pragma once
#include <string>
#include <vector>
namespace rebuntu::system::shell::sources::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
