#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
