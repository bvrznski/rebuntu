#include <runtime/phases_20_30.hpp>
#include <cassert>
#include <filesystem>
#include <iostream>
using namespace rebuntu::platform::v2030;
int main(){
 health::Predictor hp; hp.baseline("load",1); hp.observe({std::chrono::system_clock::now(),"host",{{"load","1"}}}); hp.observe({std::chrono::system_clock::now(),"host",{{"load","4"}}}); assert(hp.trend("load")>0);
 auto risk=hp.assess({{"memory-pressure","psi",.9,.1,.4,.8,true}}); assert(risk.state>=Severity::degraded); assert(!hp.plan(risk).empty());
 logs::Analyzer la; auto rec=la.parse_lines({"kernel: NVRM Xid 79 GPU has fallen off the bus","systemd: service failed"},"kernel"); assert(rec.size()==2); auto inc=la.correlate(rec); assert(!inc.empty());
 semantic_logs::BitNetBoundary sb; semantic_logs::Context cx{rec,4096,"why failed?"}; auto sr=sb.interpret(cx); assert(sb.validate(sr,cx).allowed);
 panel::ControlPanel cp; cp.publish({"health","Health",{{"state","ok"}},{{"refresh","health","Refresh",{},false,false}}, {}}); assert(cp.view("health")); assert(cp.authorize(cp.view("health")->actions[0],false,false).allowed);
 shell::Manager sh; assert(sh.record({0,"fish","echo hi","/tmp","","",0,std::chrono::milliseconds{1},false})==1); assert(!sh.search("echo").empty()); assert(sh.set_alias("ll","ls -la").allowed);
 terminal::Manager tm; assert(tm.put({"default","gnome-terminal","bash","monospace",12,{},{}})); assert(!tm.validate_paste("rm -rf /").allowed);
 dev::Manager dm; auto proj=dm.discover(std::filesystem::current_path().string()); assert(proj); auto f=dm.fingerprint(*proj); assert(!f.digest.empty());
 process::Manager pm; auto ps=pm.discover(); assert(!ps.empty()); auto ws=pm.classify(ps); assert(!ws.empty());
 resource::Manager rm; auto caps=rm.discover(); assert(!caps.empty()); assert(!rm.providers().empty());
 System2030 sys; auto closure=sys.audit(); assert(closure.ready);
 std::cout<<"phases 20-30 integration ok\n";
}
