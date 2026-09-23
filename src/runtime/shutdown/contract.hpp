#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::shutdown {
struct ShutdownContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
