#pragma once
#include "../../core/types.hpp"
#include <functional>
namespace rebuntu::control::reconciliation {
struct Cycle { core::Entity before; core::Plan plan; core::Verification after; };
using Observe=std::function<core::Entity()>; using Plan=std::function<core::Plan(const core::Entity&)>; using Apply=std::function<bool(const core::NativeOperation&)>; using Verify=std::function<core::Verification(const core::Entity&)>;
Cycle run(Observe observe, Plan plan, Apply apply, Verify verify, bool execute);
}
