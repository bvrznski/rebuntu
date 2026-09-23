#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::configuration::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
