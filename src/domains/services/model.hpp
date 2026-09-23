#pragma once
#include "../common/profiles.hpp"
namespace rebuntu::domains::services {
inline common::DomainModel model_from(const core::Entity& entity) { return common::build_model(entity, common::service_profile()); }
}
