#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::stability_and_shell::verification::probes {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
