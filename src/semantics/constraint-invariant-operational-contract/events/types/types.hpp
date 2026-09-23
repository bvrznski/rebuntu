#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::constraint_invariant_operational_contract::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
