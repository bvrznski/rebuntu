#pragma once
#include <string>
#include <vector>
namespace rebuntu::operator::gui::model::serialization {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
