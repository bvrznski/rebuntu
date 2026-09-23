#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::configuration_and_profiles::recovery::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
