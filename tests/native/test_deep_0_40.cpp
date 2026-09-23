#include <semantics/entities/state_store.hpp>
#include <planning/change_planner.hpp>
#include <security/policy/policy_engine.hpp>
#include <observation/health/health_monitor.hpp>
#include <control/reconciliation/native_reconciler.hpp>
#include <runtime/transactions/change_executor.hpp>
#include <knowledge/graph.hpp>
#include <control/domain_controller.hpp>
#include <cassert>
int main(){using namespace rebuntu;model::StateStore s;s.upsert({"svc:ssh","enabled","false","systemd"});assert(s.generation()==1);management::DomainController c(s);auto p=c.prepare({management::Domain::service,"svc:ssh","enabled","true"});assert(!p.steps.empty()&&!p.rollback.empty());policy::PolicyEngine pe;auto denied=pe.evaluate(p,{"user",false,true,{}});assert(!denied.allowed);auto allow=pe.evaluate(p,{"root",true,true,{}});assert(allow.allowed);reconciliation::Reconciler rec;auto drift=rec.diff({"svc:ssh",{{"enabled","true"}}},s);assert(drift.size()==1);transactions::ChangeExecutor ex;int n=0;auto er=ex.execute(p,allow,[&](auto const&){return ++n<2;},[](auto const&){return true;});assert(!er.ok&&er.rolled_back);health::HealthMonitor hm;hm.record({"cpu",10});hm.record({"cpu",10});hm.record({"cpu",10});hm.record({"cpu",100});assert(hm.trend("cpu").latest==100);knowledge::Graph g;g.relate({"service:ssh","depends-on","network:eth0"});g.relate({"network:eth0","uses","driver:e1000"});assert(g.reachable("service:ssh").count("driver:e1000"));return 0;}
