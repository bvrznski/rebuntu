#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::services::operations::effects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
