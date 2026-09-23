#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::stability_and_shell::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
