#pragma once
#include "../../../core/types.hpp"
#include <optional>
#include <string>
#include <string_view>
namespace rebuntu::providers::linux::filesystems {
struct MountSnapshot {
 std::string source;
 std::string target;
 std::string filesystem;
 std::string options;
 bool mounted{false};
};
class Provider {
public:
 virtual ~Provider()=default;
 // Native mount/filesystem state is authoritative. Rebuntu stores no shadow mount table.
 virtual std::optional<MountSnapshot> observe_mount(std::string_view target)=0;
 virtual bool execute(const core::NativeOperation& operation)=0;
};
}
