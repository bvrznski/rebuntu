#pragma once
#include "model.hpp"
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace rebuntu::semantics::affordances {
class Evaluator {
public:
    AffordanceResult evaluate(const CapabilityInstance& instance, const EvaluationContext& ctx) const {
        AffordanceResult out; out.evaluated_generation=ctx.observation_generation; out.evidence=instance.evidence;
        if(instance.target_id!=ctx.target_id) add(out,BlockerKind::target_mismatch,instance.definition.id,"target identity mismatch");
        if(!instance.definition.target_kinds.empty() && !instance.definition.target_kinds.contains(ctx.target_kind)) add(out,BlockerKind::target_mismatch,ctx.target_kind,"target kind is not applicable");
        if(!instance.definition.verbs.contains(ctx.verb)) add(out,BlockerKind::missing_requirement,ctx.verb,"verb is not advertised by capability");
        bool any_fresh=false, any_trusted=false;
        for(const auto& e:instance.evidence){ any_fresh |= e.fresh(ctx.now); any_trusted |= e.trusted; }
        if(instance.evidence.empty()) add(out,BlockerKind::stale_evidence,instance.definition.id,"no authoritative evidence");
        else if(!any_fresh){out.stale=true; add(out,BlockerKind::stale_evidence,instance.definition.id,"all capability evidence expired");}
        if(!instance.evidence.empty() && !any_trusted) add(out,BlockerKind::conflicting_evidence,instance.definition.id,"evidence has no trusted provenance");
        for(const auto& r:instance.definition.requirements){ auto it=ctx.facts.find(r.key); if(it==ctx.facts.end() || it->second!=r.expected){ if(r.mandatory) add(out,BlockerKind::missing_requirement,r.key,"expected="+r.expected); } }
        for(const auto& p:instance.definition.prerequisites){ bool ok=ctx.available_capabilities.contains(p.capability_id); for(const auto& alt:p.alternatives) ok |= ctx.available_capabilities.contains(alt); if(!ok) add(out,BlockerKind::prerequisite,p.capability_id,"prerequisite unavailable"); }
        if(instance.state==CapabilityState::unavailable) add(out,BlockerKind::provider_failure,instance.definition.provider,"capability unavailable");
        if(instance.state==CapabilityState::degraded) add(out,BlockerKind::provider_failure,instance.definition.provider,"capability degraded");
        if(instance.state==CapabilityState::unknown) add(out,BlockerKind::provider_failure,instance.definition.provider,"capability state unknown");
        out.authorized=ctx.authorized_verbs.contains(ctx.verb); // explicit separation: capability != permission
        if(!out.authorized) add(out,BlockerKind::policy,ctx.verb,"security policy did not authorize verb");
        const bool hard=std::any_of(out.blockers.begin(),out.blockers.end(),[](const Blocker& b){return b.kind!=BlockerKind::policy;});
        out.feasible=hard?Truth::no:Truth::yes;
        out.ready=(!hard && instance.state==CapabilityState::available && any_fresh)?Truth::yes:(instance.state==CapabilityState::unknown?Truth::unknown:Truth::no);
        return out;
    }
    bool revalidate(const CapabilityInstance& instance,const EvaluationContext& ctx,const AffordanceResult& prior) const {
        if(prior.evaluated_generation!=ctx.observation_generation) return false;
        return evaluate(instance,ctx).executable();
    }
private:
    static void add(AffordanceResult& o,BlockerKind k,std::string s,std::string d){o.blockers.push_back({k,std::move(s),std::move(d)});}
};

class PrerequisiteGraph {
public:
    void add(std::string id,std::vector<std::string> deps){edges_[std::move(id)]=std::move(deps);}
    bool has_cycle() const { std::unordered_map<std::string,int> mark; std::function<bool(const std::string&)> visit=[&](const std::string& n){ if(mark[n]==1)return true; if(mark[n]==2)return false; mark[n]=1; auto it=edges_.find(n); if(it!=edges_.end()) for(const auto& d:it->second) if(visit(d)) return true; mark[n]=2; return false;}; for(const auto& [n,_]:edges_) if(visit(n))return true; return false; }
    std::set<std::string> transitive_missing(const std::string& root,const std::set<std::string>& available,std::size_t budget=1024) const { std::set<std::string> missing,seen; std::vector<std::string> q{root}; while(!q.empty()&&seen.size()<budget){auto n=q.back();q.pop_back();if(!seen.insert(n).second)continue;auto it=edges_.find(n);if(it==edges_.end())continue;for(const auto& d:it->second){if(!available.contains(d))missing.insert(d);q.push_back(d);}} return missing; }
private: std::map<std::string,std::vector<std::string>> edges_;
};
}
