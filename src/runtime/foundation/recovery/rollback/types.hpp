#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::foundation::recovery::rollback {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
