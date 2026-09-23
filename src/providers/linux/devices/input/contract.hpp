#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::devices::input {
struct InputContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
