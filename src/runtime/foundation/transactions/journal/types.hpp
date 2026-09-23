#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::transactions::journal {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
