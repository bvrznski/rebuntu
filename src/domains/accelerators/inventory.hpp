#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::domains::gpu {
struct Device {std::string pci_address,vendor_id,device_id,class_id;std::optional<std::string>driver;bool display_controller{false};};
class Inventory {public:explicit Inventory(std::filesystem::path sys="/sys"):sys_(std::move(sys)){}std::vector<Device> pci_devices()const;std::vector<Device> display_devices()const;private:std::filesystem::path sys_;};
}
