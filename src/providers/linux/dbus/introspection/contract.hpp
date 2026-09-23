#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::providers::linux::dbus::introspection {
struct IntrospectionContract {
    std::string stable_id;
    std::string provenance;
    std::vector<std::string> evidence;
};
}
