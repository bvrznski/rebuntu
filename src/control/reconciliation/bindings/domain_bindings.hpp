#pragma once
#include "../pipeline/pipeline.hpp"
#include "../../../domains/services/reconciliation/service_controller.hpp"
#include "../../../domains/processes/reconciliation/process_controller.hpp"
#include "../../../domains/storage/reconciliation/storage_controller.hpp"
#include "../../../providers/linux/systemd/provider.hpp"
#include "../../../providers/linux/procfs/process_provider.hpp"
#include "../../../providers/linux/filesystems/provider.hpp"
#include <charconv>
#include <optional>
#include <string>

namespace rebuntu::control::reconciliation::bindings {

class AllowPolicy final : public pipeline::Policy {
public:
  pipeline::PolicyDecision authorize(const core::Plan&, const core::Entity&) override { return {}; }
};

class ServiceBinding final : public pipeline::Observer, public pipeline::Planner,
                             public pipeline::Executor, public pipeline::Verifier {
  providers::linux::systemd::Provider& provider_;
  domains::services::reconciliation::ServiceController controller_;
public:
  explicit ServiceBinding(providers::linux::systemd::Provider& p) : provider_(p), controller_(p) {}
  std::optional<pipeline::Observation> observe(const std::string& id) override;
  core::Plan synthesize(const core::DesiredState&, const core::Entity&) override;
  bool execute(const core::NativeOperation&) override;
  core::Verification verify(const core::DesiredState&, const core::Entity&) override;
};

class ProcessBinding final : public pipeline::Observer, public pipeline::Planner,
                             public pipeline::Executor, public pipeline::Verifier {
  providers::linux::procfs::ProcessProvider& provider_;
  domains::processes::reconciliation::ProcessController controller_;
  static std::optional<int> pid_from_id(const std::string&);
public:
  explicit ProcessBinding(providers::linux::procfs::ProcessProvider& p) : provider_(p), controller_(p) {}
  std::optional<pipeline::Observation> observe(const std::string& id) override;
  core::Plan synthesize(const core::DesiredState&, const core::Entity&) override;
  bool execute(const core::NativeOperation&) override;
  core::Verification verify(const core::DesiredState&, const core::Entity&) override;
};

class StorageBinding final : public pipeline::Observer, public pipeline::Planner,
                             public pipeline::Executor, public pipeline::Verifier {
  providers::linux::filesystems::Provider& provider_;
  domains::storage::reconciliation::StorageController controller_;
public:
  explicit StorageBinding(providers::linux::filesystems::Provider& p) : provider_(p), controller_(p) {}
  std::optional<pipeline::Observation> observe(const std::string& id) override;
  core::Plan synthesize(const core::DesiredState&, const core::Entity&) override;
  bool execute(const core::NativeOperation&) override;
  core::Verification verify(const core::DesiredState&, const core::Entity&) override;
};

} // namespace rebuntu::control::reconciliation::bindings
