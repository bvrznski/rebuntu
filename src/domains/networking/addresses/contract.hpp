#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::networking::addresses {
struct AddressesContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
