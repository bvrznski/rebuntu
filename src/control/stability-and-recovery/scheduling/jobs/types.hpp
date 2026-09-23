#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::stability_and_recovery::scheduling::jobs {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
