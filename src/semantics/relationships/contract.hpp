#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::relationships {
struct RelationshipsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
