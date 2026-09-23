#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::installation::lifecycle {
enum class Kind { reconfigure, repair, upgrade, uninstall, purge };
struct Artifact { std::string path; bool rebuntu_owned{false}; bool user_authored{false}; };
struct Action { std::string verb,path; };
std::vector<Action> plan_removal(Kind kind,const std::vector<Artifact>& artifacts);
}
