#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::planning::simulation {
struct SimulationContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
