// rebuntu::runtime::DBusExecutor — D-Bus Execution (Phase 0.13)
//
// Implements D-Bus method execution for remote procedure calls.

#pragma once

#include <runtime/core/contracts.hpp>
#include <chrono>
#include <string>

namespace rebuntu::runtime {

class DBusExecutor {
public:
    DBusExecutor();
    
    // Execute a D-Bus method call
    rebuntu::core::Outcome execute_dbus_method(
        const std::string& bus_name,
        const std::string& object_path,
        const std::string& interface_name,
        const std::string& method_name,
        std::chrono::milliseconds timeout = std::chrono::minutes(5));
};

}  // namespace rebuntu::runtime