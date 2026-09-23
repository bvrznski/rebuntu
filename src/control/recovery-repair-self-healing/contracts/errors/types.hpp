#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::recovery_repair_self_healing::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
