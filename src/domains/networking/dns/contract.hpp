#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::domains::networking::dns {
struct DnsContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
