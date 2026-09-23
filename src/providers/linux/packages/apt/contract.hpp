#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::packages::apt {
struct AptContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
