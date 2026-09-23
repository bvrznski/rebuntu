#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::workloads::verification {
struct VerificationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
