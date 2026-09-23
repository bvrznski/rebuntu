#pragma once
#include <string>
#include <vector>
namespace rebuntu::control::stability_and_recovery::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
