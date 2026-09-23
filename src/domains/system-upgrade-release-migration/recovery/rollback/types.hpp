#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::system_upgrade_release_migration::recovery::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
