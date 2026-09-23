#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_event_timeline::policy::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
