#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::governance::ownership {
struct OwnershipContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
