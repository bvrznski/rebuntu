#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::semantics::context {
struct ContextContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
