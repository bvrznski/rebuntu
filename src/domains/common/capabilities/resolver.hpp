#pragma once
#include "../model.hpp"
#include <algorithm>
namespace rebuntu::domains::common {
struct CapabilityRequest { std::string verb; core::Attributes context; };
struct CapabilityDecision { bool allowed{false}; std::string capability; std::vector<std::string> reasons; };
class CapabilityResolver { public:
 CapabilityDecision resolve(const DomainModel& model,const CapabilityRequest& request) const {
  CapabilityDecision out;
  for(const auto& c:model.capabilities){ if(!c.verbs.contains(request.verb)) continue; bool ok=true;
   for(const auto& [k,v]:c.constraints){auto it=request.context.find(k); if(it==request.context.end()||it->second!=v){ok=false;out.reasons.push_back("constraint "+k+"="+v+" not satisfied");}}
   if(ok){out.allowed=true;out.capability=c.name;out.reasons.clear();return out;}
  }
  if(out.reasons.empty()) { out.reasons.push_back("verb not afforded: "+request.verb); }
  return out;
 }
};
}