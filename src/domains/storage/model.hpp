#pragma once
#include "../common/profiles.hpp"
namespace rebuntu::domains::storage {
inline common::DomainModel model_from(const core::Entity& entity) { return common::build_model(entity, common::storage_profile()); }
}
