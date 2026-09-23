#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::system_upgrade_release_migration::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
