#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
