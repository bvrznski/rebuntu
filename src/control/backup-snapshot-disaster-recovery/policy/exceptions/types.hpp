#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::backup_snapshot_disaster_recovery::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
