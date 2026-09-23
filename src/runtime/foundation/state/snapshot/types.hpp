#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::state::snapshot {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
