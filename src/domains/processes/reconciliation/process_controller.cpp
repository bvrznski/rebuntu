#include "process_controller.hpp"
#include <chrono>
#include <stdexcept>
namespace rebuntu::domains::processes::reconciliation {
core::Entity ProcessController::observe(int pid) {
  const auto s=provider_.observe(pid); if(!s) throw std::runtime_error("process not observable");
  core::Entity e; e.id="process:"+std::to_string(s->pid); e.kind="process";
  e.attributes={{"pid",std::to_string(s->pid)},{"ppid",std::to_string(s->ppid)},
    {"start_ticks",std::to_string(s->start_ticks)},{"comm",s->comm},{"raw_state",s->state},{"state",(s->state=="T"||s->state=="t")?"suspended":"running"}};
  e.evidence.push_back({"procfs","linux-kernel",s->state,std::chrono::system_clock::now()}); return e;
}
core::Verification ProcessController::verify(const core::DesiredState& d,const core::Entity& a) const {
  core::Verification v; for(const auto& [k,want]:d.attributes){auto it=a.attributes.find(k); if(it==a.attributes.end()||it->second!=want) v.mismatches.push_back(k+" expected="+want+" actual="+(it==a.attributes.end()?"<missing>":it->second));}
  v.converged=v.mismatches.empty(); v.evidence=a.evidence; return v;
}
core::Plan ProcessController::plan(const core::DesiredState& d,const core::Entity& a) const {
  core::Plan p; p.id="process-reconcile:"+d.entity_id; const auto v=verify(d,a); if(v.converged) return p;
  const auto it=d.attributes.find("state"); if(it!=d.attributes.end()) {
    std::string verb; if(it->second=="stopped") verb="terminate"; else if(it->second=="running" && a.attributes.at("state")=="suspended") verb="continue";
    if(!verb.empty()) { core::Attributes args{{"start_ticks",a.attributes.at("start_ticks")}}; p.operations.push_back({"procfs",verb,a.attributes.at("pid"),args,true}); }
  }
  return p;
}
core::Verification ProcessController::reconcile(int pid,const core::DesiredState& d,bool execute) {
  auto actual=observe(pid); auto p=plan(d,actual); if(execute) for(const auto& op:p.operations) if(!provider_.execute(op)) return {false,{"native operation failed: "+op.verb},actual.evidence};
  if(!execute || p.operations.empty()) return verify(d,actual);
  try { return verify(d,observe(pid)); } catch(const std::runtime_error&) { if(d.attributes.contains("state")&&d.attributes.at("state")=="stopped") return {true,{},actual.evidence}; throw; }
}
}
