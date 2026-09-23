#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::workflow_foundation::lifecycle::hooks {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
