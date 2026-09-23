#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::workloads::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
