#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::system_upgrade_release_migration::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
