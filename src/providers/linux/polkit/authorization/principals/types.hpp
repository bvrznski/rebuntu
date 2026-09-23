#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::linux::polkit::authorization::principals {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
