#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::system_stability_homeostasis::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
