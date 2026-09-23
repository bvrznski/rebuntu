#include "service_controller.hpp"
#include <stdexcept>
namespace r=rebuntu;
namespace rebuntu::domains::services::reconciliation {
core::Entity ServiceController::observe(const std::string& unit){
 auto s=provider_.observe(unit); if(!s) throw std::runtime_error("systemd unit not observable: "+unit);
 core::Entity e; e.id="systemd:"+s->name; e.kind="service";
 e.attributes={{"name",s->name},{"load_state",s->load_state},{"active_state",s->active_state},{"sub_state",s->sub_state},{"unit_file_state",s->unit_file_state}};
 e.evidence.push_back({"systemd","systemd",s->active_state,std::chrono::system_clock::now()}); return e;
}
core::Verification ServiceController::verify(const core::DesiredState& d,const core::Entity& a) const{
 core::Verification v; for(auto& [k,want]:d.attributes){ auto it=a.attributes.find(k); if(it==a.attributes.end()||it->second!=want) v.mismatches.push_back(k+" expected="+want+" actual="+(it==a.attributes.end()?"<missing>":it->second)); }
 v.converged=v.mismatches.empty(); v.evidence=a.evidence; return v;
}
core::Plan ServiceController::plan(const core::DesiredState& d,const core::Entity& a) const{
 core::Plan p; p.id="service-reconcile:"+d.entity_id; auto v=verify(d,a); if(v.converged) return p;
 auto active=d.attributes.find("active_state"); if(active!=d.attributes.end()){
  std::string verb; if(active->second=="active") verb="start"; else if(active->second=="inactive") verb="stop"; else throw std::invalid_argument("unsupported desired active_state");
  p.operations.push_back({"systemd",verb,a.attributes.at("name"),{},true}); p.postconditions.push_back("active_state="+active->second);
 }
 auto enabled=d.attributes.find("unit_file_state"); if(enabled!=d.attributes.end()){
  std::string verb; if(enabled->second=="enabled") verb="enable"; else if(enabled->second=="disabled") verb="disable"; else throw std::invalid_argument("unsupported desired unit_file_state");
  p.operations.push_back({"systemd",verb,a.attributes.at("name"),{},true}); p.postconditions.push_back("unit_file_state="+enabled->second);
 }
 return p;
}
core::Verification ServiceController::reconcile(const core::DesiredState& d,bool execute){
 auto actual=observe(d.entity_id); auto p=plan(d,actual); if(execute) for(const auto& op:p.operations) if(!provider_.execute(op)) return {false,{"native operation failed: "+op.verb},actual.evidence}; return verify(d,observe(d.entity_id));
}
}
