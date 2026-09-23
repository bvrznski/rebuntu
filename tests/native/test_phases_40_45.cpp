#include <runtime/phases_40_45.hpp>
#include <cassert>
#include <filesystem>
using namespace rebuntu::platform::v4045;
int main(){
  SearchSystem s;s.add_provider("x",[](const Query&){return std::vector<SearchResult>{{"b","","B",.5},{"a","","A",.9},{"a","","dup",.1}};});auto rr=s.search({"",{}, {},10});assert(rr.size()==2&&rr[0].id=="a");
  WorkflowSystem w;assert(w.define("w",{{"a",{},[]{return true;},0},{"b",{"a"},[]{return true;},0}}));auto run=w.run("w");assert(run.state==RunState::succeeded&&run.completed.size()==2);
  KnowledgeGraph g;assert(g.upsert({"cpu","resource",{}}));assert(g.upsert({"svc","service",{}}));assert(g.relate({"svc","cpu","uses",{}}));assert(g.path("svc","cpu").size()==2);
  OperatorIntelligence oi;auto rec=oi.diagnose("svc",{{"procfs","svc","state","failed",.9,{}}});assert(rec.actionable);
  AdaptiveWorkstation aw;aw.protect("display");assert(!aw.propose({"bad","display","x","1","2","",1,true,false}));assert(aw.propose({"ok","cpu","governor","a","b","load",.2,true,false}));assert(aw.authorize("ok",true)&&aw.apply("ok")&&aw.rollback("ok"));
  UnifiedControlPlane cp;auto op=cp.plan("services","restart","demo.service",{},true,true,false);assert(cp.validate(op));assert(!cp.authorize(op,false));auto op2=cp.plan("services","inspect","demo.service");assert(cp.validate(op2)&&cp.authorize(op2,false)&&cp.execute(op2)&&cp.verify(op2));
  PhaseRegistry pr("../.phases"); if(std::filesystem::exists("../.phases")) assert(pr.complete());
}
