#pragma once
#include <string>
#include <vector>
namespace rebuntu::automation::autonomy_budget_delegation::contracts::errors {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
