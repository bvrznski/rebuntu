#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::system_state_and_events::state::transitions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
