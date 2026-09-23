#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::governance::invariant_audit {
struct InvariantAuditContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
