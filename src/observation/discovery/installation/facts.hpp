#pragma once
#include <chrono>
#include <string>
#include <vector>
namespace rebuntu::observation::installation {
struct Fact { std::string key; std::string value; std::string authority; std::chrono::system_clock::time_point observed_at; };
struct Snapshot { std::vector<Fact> facts; std::vector<std::string> warnings; };
Snapshot discover();
}
