#pragma once
#include "../../core/types.hpp"
#include <algorithm>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace rebuntu::domains::common {
struct ResourceIdentity { std::string stable_id; std::string kind; std::string native_authority; std::string native_key; };
struct Resource { ResourceIdentity identity; core::Attributes attributes; std::vector<core::Evidence> evidence; };
struct Relationship { std::string subject; std::string predicate; std::string object; core::Attributes attributes; };
struct Topology { std::map<std::string,Resource> nodes; std::vector<Relationship> edges;
  bool add(Resource r){ return nodes.emplace(r.identity.stable_id,std::move(r)).second; }
  bool link(Relationship e){ if(!nodes.count(e.subject)||!nodes.count(e.object)) return false; edges.push_back(std::move(e)); return true; }
};
struct Capability { std::string name; std::set<std::string> verbs; core::Attributes constraints; };
struct Requirement { std::string key; std::string expected; bool mandatory{true}; };
struct RequirementResult { bool satisfied{true}; std::vector<std::string> failures; };
inline RequirementResult evaluate(const Resource& r,const std::vector<Requirement>& reqs){ RequirementResult out; for(const auto& q:reqs){ auto it=r.attributes.find(q.key); if(it==r.attributes.end()||it->second!=q.expected){ if(q.mandatory){out.satisfied=false; out.failures.push_back(q.key+" expected="+q.expected);} } } return out; }
struct DesiredResourceState { std::string stable_id; core::Attributes attributes; std::string reason; };
struct HealthSignal { std::string name; std::string status; std::string detail; core::Evidence evidence; };
struct Health { std::vector<HealthSignal> signals; bool healthy() const { return std::none_of(signals.begin(),signals.end(),[](const auto& s){return s.status=="failed"||s.status=="degraded";}); } };
struct DomainModel { Resource resource; std::vector<Capability> capabilities; std::vector<Requirement> requirements; Health health; };
inline Resource project(const core::Entity& e,std::string authority,std::string native_key={}) { return {{e.id,e.kind,std::move(authority),native_key.empty()?e.id:std::move(native_key)},e.attributes,e.evidence}; }
inline core::DesiredState to_core(const DesiredResourceState& d){ return {d.stable_id,d.attributes,d.reason}; }
inline core::Verification verify(const DesiredResourceState& d,const Resource& r){ core::Verification v; v.converged=true; v.evidence=r.evidence; if(d.stable_id!=r.identity.stable_id){v.converged=false;v.mismatches.push_back("stable identity mismatch");} for(const auto& [k,val]:d.attributes){auto it=r.attributes.find(k);if(it==r.attributes.end()||it->second!=val){v.converged=false;v.mismatches.push_back(k+" expected="+val);}} return v; }
inline bool affords(const DomainModel& m,const std::string& verb){ for(const auto& c:m.capabilities) if(c.verbs.count(verb)) return true; return false; }
}
