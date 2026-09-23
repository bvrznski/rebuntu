#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::recovery_repair_self_healing::execution::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
