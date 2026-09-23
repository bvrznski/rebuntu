#pragma once
#include "../../common/saturation.hpp"
namespace rebuntu::domains::identity::observation {
inline common::DomainModel translate(const core::Entity& native) { auto s=common::identity_semantics(); auto m=common::build_model(native,s.profile); m.health=common::assess_attributes(native,s); return m; }
}
