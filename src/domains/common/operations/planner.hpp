#pragma once
#include "../desired_state/differ.hpp"
#include "../capabilities/resolver.hpp"
namespace rebuntu::domains::common {
struct OperationRuleV2 {
 std::string attribute; std::string desired_value; std::string verb; std::string provider; bool mutating{true}; core::Attributes arguments;
 std::string compensation_verb; std::string compensation_provider;
 OperationRuleV2(std::string a,std::string d,std::string v,std::string p,bool m=true,core::Attributes args={},std::string cv={},std::string cp={})
 :attribute(std::move(a)),desired_value(std::move(d)),verb(std::move(v)),provider(std::move(p)),mutating(m),arguments(std::move(args)),compensation_verb(std::move(cv)),compensation_provider(std::move(cp)){}
};
struct PlanningResult { core::Plan plan; std::vector<std::string> blocked; bool executable()const{return blocked.empty();} };
class OperationPlanner { public: PlanningResult plan(const DesiredResourceState& d,const DomainModel& a,const std::vector<OperationRuleV2>& rules) const {PlanningResult out;out.plan.id="domain:"+d.stable_id;auto delta=DesiredStateDiffer{}.diff(d,a.resource);for(const auto& x:delta.changes){auto r=std::find_if(rules.begin(),rules.end(),[&](const auto& z){return z.attribute==x.key&&z.desired_value==x.desired;});if(r==rules.end()){out.blocked.push_back("no operation rule for "+x.key+"="+x.desired);continue;}auto decision=CapabilityResolver{}.resolve(a,{r->verb,a.resource.attributes});if(!decision.allowed){out.blocked.push_back("capability denies "+r->verb);continue;}auto args=r->arguments;args["attribute"]=x.key;args["desired"]=x.desired;if(x.actual)args["previous"]=*x.actual;if(!r->compensation_verb.empty())args["__compensation_verb"]=r->compensation_verb;if(!r->compensation_provider.empty())args["__compensation_provider"]=r->compensation_provider;out.plan.operations.push_back({r->provider,r->verb,a.resource.identity.native_key,args,r->mutating});}out.plan.postconditions.push_back("authoritative re-observation converges");return out;} };
}