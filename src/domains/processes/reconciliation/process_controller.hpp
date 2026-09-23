#pragma once
#include "../../../core/types.hpp"
#include "../../../providers/linux/procfs/process_provider.hpp"
namespace rebuntu::domains::processes::reconciliation {
class ProcessController {
  providers::linux::procfs::ProcessProvider& provider_;
public:
  explicit ProcessController(providers::linux::procfs::ProcessProvider& provider): provider_(provider) {}
  core::Entity observe(int pid);
  core::Plan plan(const core::DesiredState&, const core::Entity&) const;
  core::Verification verify(const core::DesiredState&, const core::Entity&) const;
  core::Verification reconcile(int pid, const core::DesiredState&, bool execute);
};
}
