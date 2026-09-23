#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::system_stability_homeostasis::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
