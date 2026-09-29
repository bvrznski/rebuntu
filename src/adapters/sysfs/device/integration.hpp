// rebuntu::adapters::sysfs::device — Header for sysfs device integration
//
// This module provides the interface and factory for sysfs-based device observation.

#pragma once

#include "adapters/sysfs/device/types.hpp"

#include <memory>
#include <optional>

namespace rebuntu::adapters::sysfs::device {

// Factory function to create a new sysfs device adapter instance
std::unique_ptr<SysfsDeviceAdapter> make_sysfs_device_adapter();

// Factory function with custom options
std::unique_ptr<SysfsDeviceAdapter> make_sysfs_device_adapter(const SysfsDeviceOptions& opts);

}  // namespace rebuntu::adapters::sysfs::device
