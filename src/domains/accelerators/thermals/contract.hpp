#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::accelerators::thermals {
struct ThermalsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
