#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::configuration_and_profiles::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
