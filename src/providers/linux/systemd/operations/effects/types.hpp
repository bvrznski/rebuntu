#pragma once
#include <string>
#include <vector>
namespace rebuntu::providers::linux::systemd::operations::effects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
