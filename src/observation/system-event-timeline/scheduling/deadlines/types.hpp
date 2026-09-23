#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_event_timeline::scheduling::deadlines {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
