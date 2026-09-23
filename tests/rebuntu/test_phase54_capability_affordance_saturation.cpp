#include "semantics/affordances/evaluator.hpp"
#include "semantics/affordances/registry.hpp"
#include "semantics/affordances/explanation.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu::semantics::affordances;
int main(){
 auto now=std::chrono::system_clock::now();
 CapabilityDefinition d{"service.restart","systemd",{"restart"},{{"state","active",true}},{{"network.ready",{"network.online"}}},{"service"}};
 Evidence e{"systemd-provider","systemd","unit","active",7,now,std::chrono::seconds{30},true};
 CapabilityInstance i{d,"svc:ssh",CapabilityState::available,{e}};
 EvaluationContext c{"svc:ssh","service","restart",{{"state","active"}},{"network.ready"},{"restart"},7,now};
 Evaluator ev; auto ok=ev.evaluate(i,c); assert(ok.executable()); std::cout<<"AFFORDANCE_EXECUTABLE_PASS\n";
 auto denied=c; denied.authorized_verbs.clear(); auto no=ev.evaluate(i,denied); assert(!no.executable() && !no.authorized); std::cout<<"CAPABILITY_NOT_PERMISSION_PASS\n";
 auto stale=c; stale.now=now+std::chrono::seconds{31}; auto sr=ev.evaluate(i,stale); assert(sr.stale&&!sr.executable()); std::cout<<"STALE_EVIDENCE_FAIL_CLOSED_PASS\n";
 auto changed=c; changed.observation_generation=8; assert(!ev.revalidate(i,changed,ok)); std::cout<<"PRE_EXECUTION_REVALIDATION_PASS\n";
 PrerequisiteGraph g;g.add("a",{"b"});g.add("b",{"c"});g.add("c",{"a"});assert(g.has_cycle());std::cout<<"PREREQUISITE_CYCLE_PASS\n";
 Registry reg; assert(reg.advertise(i)); auto q=reg.query("restart","service",now);assert(q.size()==1);assert(reg.invalidate_authority("systemd")==1);assert(reg.query("restart","service",now).empty());std::cout<<"REGISTRY_INVALIDATION_PASS\n";
 assert(explain(no).find("security policy")!=std::string::npos);std::cout<<"WHY_NOT_EXPLANATION_PASS\n";
}
