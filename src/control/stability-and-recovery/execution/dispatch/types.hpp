#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::stability_and_recovery::execution::dispatch {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
