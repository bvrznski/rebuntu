#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::reconciliation::events::subscriptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
