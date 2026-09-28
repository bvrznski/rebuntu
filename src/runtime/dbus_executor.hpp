// rebuntu::runtime::DBusExecutor — D-Bus Execution (Phase 0.13)
//
// Implements D-Bus method execution for remote procedure calls.

#pragma once

#include <system/core/contracts.hpp>
#include <chrono>
#include <string>

namespace rebuntu::runtime {

struct DBusMethodCall {
    std::string bus_name;
    std::string object_path;
    std::string interface_name;
    std::string method_name;
    std::chrono::milliseconds timeout{30000};  // Default 30 second timeout
};

class DBusExecutor {
public:
    DBusExecutor();
    
    // Execute a D-Bus method call
    rebuntu::core::Outcome execute_dbus_method(DBusMethodCall call);
};

}  // namespace rebuntu::runtime
