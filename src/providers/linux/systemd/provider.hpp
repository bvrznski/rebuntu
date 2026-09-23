#pragma once
#include "../../../core/types.hpp"
#include <optional>
#include <string_view>
namespace rebuntu::providers::linux::systemd {
struct UnitSnapshot { std::string name, load_state, active_state, sub_state, unit_file_state; };
class Provider {
public:
 virtual ~Provider()=default;
 virtual std::optional<UnitSnapshot> observe(std::string_view unit)=0;
 virtual bool execute(const core::NativeOperation& op)=0;
};
}
