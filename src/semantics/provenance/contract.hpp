#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::provenance {
struct ProvenanceContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
