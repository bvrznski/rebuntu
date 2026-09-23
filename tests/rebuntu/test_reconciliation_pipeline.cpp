#include "control/reconciliation/pipeline/pipeline.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
namespace p=control::reconciliation::pipeline;
struct F: p::Observer,p::Planner,p::Policy,p::Executor,p::Verifier {
 bool running=false, allow=true; int executions=0;
 std::optional<p::Observation> observe(const std::string& id) override { core::Entity e{id,"service",{{"state",running?"running":"stopped"}},{{"fake","test","state"}}}; return p::Observation{e,true}; }
 core::Plan synthesize(const core::DesiredState& d,const core::Entity&) override { core::Plan x{"plan", {}, {}, {}}; x.operations.push_back({"fake-native","start",d.entity_id,{},true}); return x; }
 p::PolicyDecision authorize(const core::Plan&,const core::Entity&) override { return {allow,allow?std::vector<std::string>{}:std::vector<std::string>{"policy-denied"}}; }
 bool execute(const core::NativeOperation&) override { ++executions; running=true; return true; }
 core::Verification verify(const core::DesiredState& d,const core::Entity& e) override { core::Verification v; v.converged=e.attributes.at("state")==d.attributes.at("state"); if(!v.converged)v.mismatches.push_back("state"); return v; }
};
int main(){ core::DesiredState d{"svc",{{"state","running"}},"test"};
 {F f;p::Pipeline q(f,f,f,f,f);auto r=q.reconcile(d,false);assert(r.status==p::Result::Status::planned);assert(f.executions==0);}
 {F f;f.allow=false;p::Pipeline q(f,f,f,f,f);auto r=q.reconcile(d,true);assert(r.status==p::Result::Status::blocked);assert(f.executions==0);}
 {F f;p::Pipeline q(f,f,f,f,f);auto r=q.reconcile(d,true);assert(r.status==p::Result::Status::applied);assert(f.executions==1);assert(r.verification.converged);}
 {F f;f.running=true;p::Pipeline q(f,f,f,f,f);auto r=q.reconcile(d,true);assert(r.status==p::Result::Status::converged);assert(f.executions==0);}
 std::cout<<"RECONCILIATION_PIPELINE_PASS\n"; }
