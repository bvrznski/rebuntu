#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_event_timeline::contracts::inputs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
