#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::networking::interfaces {
struct InterfacesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
