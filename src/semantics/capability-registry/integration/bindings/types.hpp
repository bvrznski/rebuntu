#pragma once
#include <string>
#include <vector>
namespace rebuntu::semantics::capability_registry::integration::bindings {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
