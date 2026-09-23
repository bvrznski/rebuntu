#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::stability_and_recovery::transactions::commit {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
