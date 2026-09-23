#pragma once
#include "../preflight/host_preflight.hpp"
#include <string>
#include <vector>
namespace rebuntu::runtime::installation {
enum class DependencyClass { bootstrap, runtime, optional_feature, development, provider_specific };
struct Dependency { std::string name; DependencyClass classification{DependencyClass::runtime}; bool required{true}; };
struct Step { std::string id; std::string target; std::string action; std::vector<std::string> prerequisites; bool privileged{false}; bool mutating{false}; std::string verification; bool checkpoint{false}; };
struct Intent { std::string install_root; std::vector<Dependency> dependencies; bool dry_run{true}; };
struct Plan { std::string target_state; std::vector<Step> steps; std::vector<std::string> warnings; bool executable{false}; bool dry_run{true}; };
class Planner { public: Plan build(const Intent&, const preflight::Report&) const; };
}
