#pragma once
#include <map>
#include <string>
#include <vector>
namespace rebuntu::setup::profile {
struct Input { std::map<std::string,std::string> explicit_values, preferences, discovered, policy; };
struct Derived { std::map<std::string,std::string> values, provenance; };
Derived derive(const Input& in);
}
