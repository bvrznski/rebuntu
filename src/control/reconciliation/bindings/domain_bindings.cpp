#include "domain_bindings.hpp"
#include <stdexcept>
namespace rebuntu::control::reconciliation::bindings {
std::optional<pipeline::Observation> ServiceBinding::observe(const std::string& id) {
  try { return pipeline::Observation{controller_.observe(id), true}; } catch (const std::runtime_error&) { return std::nullopt; }
}
core::Plan ServiceBinding::synthesize(const core::DesiredState& d,const core::Entity& a){ return controller_.plan(d,a); }
bool ServiceBinding::execute(const core::NativeOperation& op){ return provider_.execute(op); }
core::Verification ServiceBinding::verify(const core::DesiredState& d,const core::Entity& a){ return controller_.verify(d,a); }

std::optional<int> ProcessBinding::pid_from_id(const std::string& id) {
  const auto raw=id.rfind("process:",0)==0 ? id.substr(8) : id;
  int pid{}; const auto* begin=raw.data(); const auto* end=begin+raw.size();
  auto [ptr,ec]=std::from_chars(begin,end,pid); if(ec!=std::errc{}||ptr!=end||pid<=0) return std::nullopt; return pid;
}
std::optional<pipeline::Observation> ProcessBinding::observe(const std::string& id) {
  auto pid=pid_from_id(id); if(!pid) return std::nullopt;
  try { return pipeline::Observation{controller_.observe(*pid), true}; } catch (const std::runtime_error&) { return std::nullopt; }
}
core::Plan ProcessBinding::synthesize(const core::DesiredState& d,const core::Entity& a){ return controller_.plan(d,a); }
bool ProcessBinding::execute(const core::NativeOperation& op){ return provider_.execute(op); }
core::Verification ProcessBinding::verify(const core::DesiredState& d,const core::Entity& a){ return controller_.verify(d,a); }

std::optional<pipeline::Observation> StorageBinding::observe(const std::string& id) {
  return pipeline::Observation{controller_.observe_mount(id), true};
}
core::Plan StorageBinding::synthesize(const core::DesiredState& d,const core::Entity& a){ return controller_.plan(d,a); }
bool StorageBinding::execute(const core::NativeOperation& op){ return provider_.execute(op); }
core::Verification StorageBinding::verify(const core::DesiredState& d,const core::Entity& a){ return controller_.verify(d,a); }
}
