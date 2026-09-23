#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::contracts::invariants {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
