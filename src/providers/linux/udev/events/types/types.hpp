#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::linux::udev::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
