#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::workflow_foundation::transactions::intent {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
