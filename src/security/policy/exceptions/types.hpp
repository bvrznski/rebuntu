#pragma once
#include <string>
#include <vector>
namespace rebuntu::security::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
