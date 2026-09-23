#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::capabilities {
struct CapabilitiesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
