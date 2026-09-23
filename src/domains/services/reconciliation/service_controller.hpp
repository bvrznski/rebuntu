#pragma once
#include "../../../core/types.hpp"
#include "../../../providers/linux/systemd/provider.hpp"
#include <optional>
namespace rebuntu::domains::services::reconciliation {
class ServiceController {
 providers::linux::systemd::Provider& provider_;
public:
 explicit ServiceController(providers::linux::systemd::Provider& p):provider_(p){}
 core::Entity observe(const std::string& unit);
 core::Plan plan(const core::DesiredState& desired, const core::Entity& actual) const;
 core::Verification verify(const core::DesiredState& desired, const core::Entity& actual) const;
 core::Verification reconcile(const core::DesiredState& desired, bool execute);
};
}
