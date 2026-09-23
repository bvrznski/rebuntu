#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::process_workload_management::integration::bindings {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
