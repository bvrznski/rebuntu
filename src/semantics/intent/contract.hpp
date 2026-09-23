#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::intent {
struct IntentContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
