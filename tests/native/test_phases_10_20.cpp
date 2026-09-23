#include <runtime/phases_10_20.hpp>
#include <cassert>
#include <fstream>
using namespace rebuntu::platform;
int main(){
 System s;
 s.workflow.register_capability("echo",[](const workflow::Step&x,const Fields&){return workflow::StepResult{x.id,Status::succeeded,{{"value","ok"}},{{"test","echo","ran",true}},1};});
 workflow::Definition wd{"wf","1",{{"a","echo",{},{{"x","1"}},{1,{}},true,""},{"b","echo",{"a"},{},{1,{}},false,""}}};
 assert(s.workflow.validate(wd).empty()); auto wr=s.workflow.run(wd); assert(wr.status==Status::succeeded&&wr.verified);
 s.configuration.set({"mode","safe","defaults",config::Layer::defaults});s.configuration.set({"mode","fast","runtime",config::Layer::runtime});assert(s.configuration.get("mode")=="fast");
 s.stability.baseline({{{"service","active"}}});assert(s.stability.deviations({{"service","active"}}).empty());
 security::Principal p{"u",{"admin"},{"destructive"},{"system"},true};s.security.policy("restart",{"admin"});security::Request rq{"restart","system",{},false};auto ad=s.security.authorize(p,rq);assert(ad.allowed);s.security.record(p,rq,ad);assert(!s.security.audit().empty());auto sec=s.security.seal_secret("abc");assert(s.security.open_secret(sec)=="abc");
 auto rs=s.resources.discover();assert(rs.cpu_count>0);assert(s.resources.validate({"normal",100,0,std::nullopt,0},rs).allowed);
 auto dev=s.environment.discover();(void)dev;assert(!s.environment.interfaces().empty());
 auto fs=s.maintenance.filesystem_state("/");assert(fs.contains("total_bytes"));
 auto in=s.semantic.parse("restart service name=demo");auto ir=s.semantic.lower(in);assert(s.semantic.safety(ir,{"restart.service"}).allowed);
 assert(s.capabilities.add({"restart.service","1","systemd",{"service"},true,true}));assert(s.capabilities.gap({"restart.service"}).missing.empty());
 Fields desired{{"a","1"}}, observed{{"a","0"}};auto rr=s.reconciler.converge(desired,observed,[](const reconcile::Delta&){return true;});assert(rr.converged);
 auto audit=s.audit();assert(audit.healthy);
 return 0;
}
