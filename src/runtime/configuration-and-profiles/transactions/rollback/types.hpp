#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::configuration_and_profiles::transactions::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
