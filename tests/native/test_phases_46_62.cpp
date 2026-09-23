#include <runtime/phases_46_53.hpp>
#include <runtime/phases_54_62.hpp>
#include <cassert>
#include <filesystem>
using namespace rebuntu::platform;
int main(){
 namespace a=v4653; namespace b=v5462;
 v4045::UnifiedControlPlane cp; a::TaskPolicyEngine policy; policy.add({"local-read",10,{"ask"},{"inspect"},{"*"},{"operator"},{},a::Decision::allow,a::Risk::low,true,true,false});
 a::Principal who{"u",{"operator"},{"task:inspect"},true}; a::TaskContext ctx;ctx.cwd="/tmp";ctx.session="s";ctx.host="h";
 a::NaturalLanguageOperator ask(cp);ask.policy(&policy);ask.semantic_provider([](auto&,auto&){return std::vector<a::IntentCandidate>{{"inspect","cpu",{},.99,false,false,false,{}}};});auto rep=ask.ask("inspect cpu",who,ctx);assert(rep.decision==a::Decision::allow&&rep.operation&&rep.operation->state==v4045::OperationState::verified);
 a::ContextEngine ce;ce.source("env",[](auto&k)->std::optional<std::pair<std::string,a::Provenance>>{return std::pair{k=="mode"?"normal":"unknown",a::Provenance{"env","local","read"}};});assert(ce.capture("/","s","h",{"mode"}).facts.size()==1);
 a::LinuxAdapter linux;assert(linux.inspect().os=="linux");
 a::Fabric fabric;assert(fabric.admit({"n1","local",{"task:inspect"}}));a::Task t{"t","ask","inspect","cpu",who,ctx,{},a::Risk::low,false,false,false,true,{"task:inspect"},{}};auto rr=fabric.dispatch(t,"n1",[](auto&,auto&){return a::RemoteResult{true,true,false,"ok"};});assert(rr.completed);
 a::AssociationManager am;assert(am.local({"self","fp","pub",1,false}));assert(am.associate({"peer","fp2","pub2",1,false},"proof"));auto g=am.grant("peer",{"inspect"},std::chrono::seconds(10));assert(g&&am.authorize(g->id,"inspect"));assert(am.revoke(g->id)&&!am.authorize(g->id,"inspect"));
 a::Label low{a::Secrecy::internal,a::Integrity::high,{"ops"}}, high{a::Secrecy::secret,a::Integrity::normal,{"ops"}};assert(a::InformationFlow::can_flow(low,high));
 b::DesiredStateRuntime rt;rt.capabilities.observe({"set-mode","local",b::Availability::available});rt.planner.add_operator("mode",[](auto&g,auto&,auto&){std::vector<b::PlanStep>r;if(auto i=g.desired.find("mode");i!=g.desired.end())r.push_back({"s","set","mode",{{"mode",i->second}},{"set-mode"},1,true});return r;});rt.contracts.add({"mode-known","",b::Severity::error,[](auto&){return true;},true});assert(rt.goals.put({"g","set mode",{{"mode","quiet"}},10,b::GoalState::active}));auto rec=rt.maintain("g");assert(rec.converged&&rt.world.values["mode"]=="quiet");
 b::ImpactAnalyzer ia;ia.add("base",[](auto&c,auto&){return std::vector<b::Impact>{{c.target,"bounded",b::Severity::info,1,true}};});b::Change ch{"c","set","mode",{},{{"mode","quiet"}},false,false};auto impacts=ia.analyze(ch,rt.world);assert(ia.acceptable(impacts));auto tx=rt.transactions.begin(ch);assert(rt.transactions.prepare(tx,rt.contracts.evaluate(rt.world),impacts));assert(rt.transactions.commit(tx,[](auto&){return true;},[](auto&){return true;},[](auto&){return true;}));
 b::Incident in{"i","svc","down"};rt.recovery.register_repair({"restart",{"down"},[](auto&i){i.symptom="up";return true;},1,false});assert(rt.recovery.recover(in));rt.homeostasis.observe({"cpu",50,0,90,1});assert(rt.homeostasis.assess().stable);
 auto root=std::filesystem::exists(".phases/PHASES")?".phases/PHASES":"../.phases/PHASES";a::PhaseCoverage ca(root);b::PhaseCoverage cb(root);assert(ca.complete());assert(cb.complete());
}
