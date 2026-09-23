#pragma once
#include <string>
#include <vector>
namespace rebuntu::system::shell::sources::execution::cancellation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
