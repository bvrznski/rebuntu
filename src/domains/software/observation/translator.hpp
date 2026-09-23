#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::software::observation {
inline common::DomainModel translate(const core::Entity& native) { auto s=common::software_semantics(); auto m=common::build_model(native,s.profile); m.health=common::assess_attributes(native,s); return m; }
}
