#pragma once
#include <map>
#include <string>
#include <vector>
namespace rebuntu::setup::configuration {
enum class Ownership { managed, user_owned, merge_managed, external };
struct Entry { std::string key; std::string value; std::string source; };
struct Document { std::string path; Ownership ownership{Ownership::managed}; std::vector<Entry> entries; };
struct Diff { std::vector<Entry> set; std::vector<std::string> remove; bool empty() const { return set.empty()&&remove.empty(); } };
Diff diff(const Document& current,const Document& desired);
}
