#include <runtime/phases_0_40_complete.hpp>
#include <cassert>
#include <iostream>
using namespace rebuntu::platform::v0040;
int main(){
  System0040 s(".phases/PHASES"); auto a=s.audit(); std::cerr<<"ready="<<a.ready<<" count="<<a.prompt_count<<" issues="<<a.issues.size()<<"\n"; for(auto&x:a.issues) std::cerr<<x<<"\n"; assert(a.ready); assert(a.phase_prompts.size()==41); assert(a.prompt_count>1000);
  WorkflowPlan w{"x",{{"observe",{},0,true},{"plan",{"observe"},0,true},{"apply",{"plan"},1,true},{"verify",{"apply"},0,true}}}; assert(s.workflows.validate(w).empty()); assert(s.workflows.order(w).size()==4);
  ChangePlan p{"1","configuration","apply","/tmp/example",{},Risk::high,true,true,{"target exists"},{"snapshot","atomic-write"},{"parse","compare"},{"restore snapshot"}}; assert(s.policy.validate(p)); assert(!s.policy.authorize(p,false,true).allowed); assert(s.policy.authorize(p,true,true).allowed);
  auto h=s.inventory.collect(); assert(!h.memory.empty()); assert(!h.processes.empty());
  SearchEngine se; se.index(h); Query q; q.text="system-memory"; auto r=se.search(q); assert(r.total>=1); assert(!se.complete("system").empty());
  HealthEngine he; auto ha=he.assess("gpu",{{"gpu","temperature",92,80,90,{}}}); assert(ha.state=="critical");
  SecretRedactor red; assert(red.redact("token=abcdef").find("abcdef")==std::string::npos);
  EventCorrelator ec; auto now=std::chrono::system_clock::now(); auto groups=ec.correlate({{now,"kernel","x","a","one"},{now+std::chrono::seconds(1),"systemd","x","a","two"}},std::chrono::seconds(5)); assert(groups.size()==1&&groups[0].size()==2);
  ConfigurationTransaction tx; std::string tp="/tmp/rebuntu-phase0040-test.conf"; auto tr=tx.apply(tp,"a=1\n",true); assert(tr.ok); auto tr2=tx.apply(tp,"a=2\n",true); assert(tr2.ok&&!tr2.backup.empty()); assert(tx.rollback(tp,tr2.backup)); std::remove(tp.c_str()); std::remove(tr2.backup.c_str());
  assert(s.commands.resolve("restart-service")); assert(!s.commands.resolve("definitely-not-a-command"));
  std::cout<<"phase0-40 prompts="<<a.prompt_count<<" processes="<<h.processes.size()<<" entities-found="<<r.total<<"\n";
}
