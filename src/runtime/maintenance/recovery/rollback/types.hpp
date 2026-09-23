#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::maintenance::recovery::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
