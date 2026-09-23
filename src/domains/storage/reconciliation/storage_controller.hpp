#pragma once
#include "../../../core/types.hpp"
#include "../../../providers/linux/filesystems/provider.hpp"
namespace rebuntu::domains::storage::reconciliation {
class StorageController {
 providers::linux::filesystems::Provider& provider_;
public:
 explicit StorageController(providers::linux::filesystems::Provider& provider):provider_(provider){}
 core::Entity observe_mount(const std::string& target);
 core::Verification verify(const core::DesiredState& desired,const core::Entity& actual) const;
 core::Plan plan(const core::DesiredState& desired,const core::Entity& actual) const;
 core::Verification reconcile(const core::DesiredState& desired,bool execute);
};
}
