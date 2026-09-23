#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::configuration_and_profiles::desired_state::model {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
