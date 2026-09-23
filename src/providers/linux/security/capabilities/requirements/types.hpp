#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::linux::security::capabilities::requirements {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
