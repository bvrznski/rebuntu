#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::ownership {
struct OwnershipContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
