#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::distributed_rebuntu_system::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
