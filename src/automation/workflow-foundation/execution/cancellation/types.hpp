#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::workflow_foundation::execution::cancellation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
