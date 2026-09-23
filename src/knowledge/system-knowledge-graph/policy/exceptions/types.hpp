#pragma once
#include <string>
#include <vector>
namespace rebuntu::knowledge::system_knowledge_graph::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
