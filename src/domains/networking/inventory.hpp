#pragma once
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::domains::network {
struct Interface {std::string name; bool up{false}; std::uint64_t mtu{0},rx_bytes{0},tx_bytes{0}; std::optional<std::string> address,operstate;};
struct Route {std::string interface,destination,gateway; std::uint32_t flags{0};};
class Inventory {public: explicit Inventory(std::filesystem::path sys="/sys",std::filesystem::path proc="/proc"):sys_(std::move(sys)),proc_(std::move(proc)){} std::vector<Interface> interfaces()const;std::vector<Route> ipv4_routes()const;private:std::filesystem::path sys_,proc_;};
}
