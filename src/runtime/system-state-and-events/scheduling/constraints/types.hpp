#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::system_state_and_events::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
