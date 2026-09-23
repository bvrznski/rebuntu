#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_rebuntu_system::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
