#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::configuration_and_profiles::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
