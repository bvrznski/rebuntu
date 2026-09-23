#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::linux::polkit::authorization::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
