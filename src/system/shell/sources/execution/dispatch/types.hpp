#pragma once
#include <string>
#include <vector>
namespace rebuntu::system::shell::sources::execution::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
