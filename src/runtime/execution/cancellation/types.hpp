#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::execution::cancellation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
