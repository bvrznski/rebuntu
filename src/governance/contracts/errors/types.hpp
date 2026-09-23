#pragma once
#include <string>
#include <vector>
namespace rebuntu::governance::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
