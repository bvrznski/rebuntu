#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::distributed::federation {
struct FederationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
