#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::recovery_repair_self_healing::contracts::outputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
