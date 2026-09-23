#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::policy::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
