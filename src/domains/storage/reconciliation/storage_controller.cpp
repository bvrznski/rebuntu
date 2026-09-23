#include "storage_controller.hpp"
#include <stdexcept>
namespace rebuntu::domains::storage::reconciliation {
core::Entity StorageController::observe_mount(const std::string& target) {
 auto snapshot=provider_.observe_mount(target);
 core::Entity e; e.id="mount:"+target; e.kind="storage.mount";
 if(snapshot){
  e.attributes={{"target",snapshot->target},{"source",snapshot->source},{"filesystem",snapshot->filesystem},{"options",snapshot->options},{"mounted",snapshot->mounted?"true":"false"}};
  e.evidence.push_back({"linux.filesystems","kernel mount state",snapshot->mounted?"mounted":"unmounted",std::chrono::system_clock::now()});
 } else {
  e.attributes={{"target",target},{"mounted","false"}};
  e.evidence.push_back({"linux.filesystems","kernel mount state","not present",std::chrono::system_clock::now()});
 }
 return e;
}
core::Verification StorageController::verify(const core::DesiredState& d,const core::Entity& a) const {
 core::Verification v; for(const auto& [key,want]:d.attributes){ auto it=a.attributes.find(key); if(it==a.attributes.end()||it->second!=want) v.mismatches.push_back(key+" expected="+want+" actual="+(it==a.attributes.end()?"<missing>":it->second)); }
 v.converged=v.mismatches.empty(); v.evidence=a.evidence; return v;
}
core::Plan StorageController::plan(const core::DesiredState& d,const core::Entity& a) const {
 core::Plan p; p.id="storage-reconcile:"+d.entity_id; if(verify(d,a).converged) return p;
 const auto desired_mounted=d.attributes.find("mounted");
 if(desired_mounted==d.attributes.end()) return p;
 if(desired_mounted->second=="true") {
  auto src=d.attributes.find("source"); auto fs=d.attributes.find("filesystem");
  if(src==d.attributes.end()||fs==d.attributes.end()) throw std::invalid_argument("mount desired state requires source and filesystem");
  core::Attributes args{{"source",src->second},{"filesystem",fs->second}};
  if(auto o=d.attributes.find("options");o!=d.attributes.end()) args["options"]=o->second;
  p.operations.push_back({"linux.filesystems","mount",a.attributes.at("target"),std::move(args),true});
 } else if(desired_mounted->second=="false") {
  p.operations.push_back({"linux.filesystems","unmount",a.attributes.at("target"),{},true});
 } else throw std::invalid_argument("mounted must be true or false");
 p.postconditions.push_back("mounted="+desired_mounted->second); return p;
}
core::Verification StorageController::reconcile(const core::DesiredState& d,bool execute) {
 auto before=observe_mount(d.entity_id); auto p=plan(d,before);
 if(execute) for(const auto& op:p.operations) if(!provider_.execute(op)) return {false,{"native filesystem operation failed: "+op.verb},before.evidence};
 return verify(d,observe_mount(d.entity_id));
}
}
