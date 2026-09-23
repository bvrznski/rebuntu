#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::stability_and_recovery::execution::requests {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
