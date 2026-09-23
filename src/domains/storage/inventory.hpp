#pragma once
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::domains::storage {
struct Mount { std::string source,target,filesystem,options; int major{-1},minor{-1}; };
struct BlockDevice { std::string name,path; std::uint64_t sectors{0},logical_block_size{512},size_bytes{0}; bool rotational{false},removable{false},read_only{false}; std::optional<std::string> model,vendor; };
class Inventory {
public:
 explicit Inventory(std::filesystem::path sys_root="/sys", std::filesystem::path proc_root="/proc"):sys_(std::move(sys_root)),proc_(std::move(proc_root)){}
 std::vector<BlockDevice> block_devices() const;
 std::vector<Mount> mounts() const;
 std::optional<Mount> mount_for(const std::filesystem::path&) const;
private: std::filesystem::path sys_,proc_;
};
}
