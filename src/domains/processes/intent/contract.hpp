#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::processes::intent {
struct IntentContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
