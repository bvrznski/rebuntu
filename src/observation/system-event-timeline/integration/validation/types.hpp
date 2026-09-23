#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_event_timeline::integration::validation {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
