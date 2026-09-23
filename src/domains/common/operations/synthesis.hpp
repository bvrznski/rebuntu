#pragma once
#include "../model.hpp"
#include <functional>
namespace rebuntu::domains::common::operations {
struct OperationRule { std::string attribute; std::string desired_value; std::string verb; std::string provider; bool mutating{true}; };
struct SynthesisResult { core::Plan plan; std::vector<std::string> unsupported; };
inline SynthesisResult synthesize(const DesiredResourceState& desired,const DomainModel& actual,const std::vector<OperationRule>& rules){
 SynthesisResult out; out.plan.id="reconcile:"+desired.stable_id;
 for(const auto& [key,value]:desired.attributes){ auto ai=actual.resource.attributes.find(key); if(ai!=actual.resource.attributes.end()&&ai->second==value) continue;
   auto ri=std::find_if(rules.begin(),rules.end(),[&](const auto& r){return r.attribute==key&&r.desired_value==value;});
   if(ri==rules.end()||!affords(actual,ri->verb)){ out.unsupported.push_back(key+"="+value); continue; }
   core::NativeOperation op{ri->provider,ri->verb,desired.stable_id,{{"attribute",key},{"desired",value}},ri->mutating}; out.plan.operations.push_back(std::move(op));
 }
 out.plan.postconditions.push_back("desired state verified by authoritative re-observation"); return out;
}
}
