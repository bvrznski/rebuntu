#include "runtime/preflight/host_preflight.hpp"
#include "runtime/installation/installation_plan.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu::runtime;
static preflight::Fact fact(std::string k,std::string v){return {std::move(k),std::move(v),"test",true};}
int main(){
 std::map<std::string,preflight::Fact> fs;
 fs["architecture"]=fact("architecture","x86_64"); fs["distribution"]=fact("distribution","ubuntu"); fs["systemd"]=fact("systemd","available"); fs["package_manager"]=fact("package_manager","apt"); fs["root_free_bytes"]=fact("root_free_bytes","9999999999");
 auto r=preflight::HostPreflight::evaluate(fs); assert(r.ready()); assert(r.support==preflight::SupportLevel::tested); assert(r.human_summary().find("READY")!=std::string::npos);
 fs["architecture"]=fact("architecture","mips"); auto blocked=preflight::HostPreflight::evaluate(fs); assert(!blocked.ready());
 installation::Intent i{"/opt/rebuntu",{{"libfoo",installation::DependencyClass::runtime,true},{"debug-tool",installation::DependencyClass::development,false}},true};
 installation::Planner planner; auto p=planner.build(i,r); assert(p.executable); assert(p.dry_run); assert(p.steps.size()==4); assert(p.steps[1].id=="dependency-libfoo"); assert(!p.warnings.empty());
 auto bp=planner.build(i,blocked); assert(!bp.executable);
 bool threw=false; try { planner.build({"relative",{},true},r); } catch(const std::invalid_argument&){threw=true;} assert(threw);
 std::cout<<"PREFLIGHT_PLANNING_PASS\n";
}
