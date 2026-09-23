#include <control/homeostasis/contracts.hpp>
#include <domains/shell/language.hpp>
#include <observation/observation.hpp>
#include <runtime/events/engine.hpp>
#include <automation/workflows/automation_runtime.hpp>
#include <cassert>
#include <chrono>
int main(){using namespace std::chrono_literals;
 {rebuntu::stability::StabilityService s(2);s.ingest(rebuntu::stability::JournalNormalizer::normalize("NVIDIA GPU critical error"));auto x=s.snapshot();assert(x.events.size()==1&&x.alerts.size()==1);s.acknowledge("gpu-health");assert(s.snapshot().alerts[0].acknowledged);}
 {rebuntu::shell::Parser p;auto r=p.parse("show service failed --format=json");assert(r.ok&&r.command.object=="service"&&r.command.qualifiers.size()==1);auto n=p.parse("grep foo file");assert(n.ok&&n.command.native_fallback);}
 {rebuntu::observation::StateView v;using rebuntu::observation::Observation;using rebuntu::observation::Provenance;v.observe(Observation{"service","sshd","running",Provenance{"systemd",rebuntu::observation::Quality::authoritative}});v.observe(Observation{"service","sshd","failed",Provenance{"systemd",rebuntu::observation::Quality::authoritative}});assert(v.history().size()==1);assert(!rebuntu::observation::observe_procfs().empty());}
 {rebuntu::events::Engine e;e.add_rule({"failed",{"c",[](auto&a){return a.predicate=="failed";}},"failure"});auto v=e.ingest({"1","failed","systemd","sshd","exit"});assert(v.size()==1);assert(e.correlate("sshd",5s).size()==1);}
 {rebuntu::workflow::AutomationRuntime a;int n=0;assert(a.register_automaton({"x","X",{rebuntu::workflow::TriggerKind::event,"failed"},{1,0ms,true},[&]{++n;return true;}}));auto ev=a.trigger("x");assert(ev&&ev->result==rebuntu::workflow::RunState::succeeded&&n==1);rebuntu::workflow::WorkflowRuntime wr;rebuntu::workflow::Workflow w{"w",{{"a",[]{return true;},{}},{"b",[]{return true;},{"a"}}}};assert(wr.run(w)&&wr.completed().size()==2);}
}