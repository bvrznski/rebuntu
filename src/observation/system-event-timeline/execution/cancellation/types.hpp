#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_event_timeline::execution::cancellation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
