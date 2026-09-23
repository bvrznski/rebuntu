#include "runtime/preferences/resolver.hpp"
#include "portability/setup/configuration/model.hpp"
#include "portability/setup/profile/bootstrap.hpp"
#include "runtime/installation/lifecycle/operations.hpp"
#include "runtime/installation/verification/invariants.hpp"
#include "observation/discovery/installation/facts.hpp"
#include <cassert>
#include <iostream>
int main(){
 using namespace rebuntu;
 auto p=runtime::preferences::resolve({{"system",10,"podman"},{"user",20,"docker"}}, {"podman"}, "podman"); assert(p.effective&&*p.effective=="podman"&&!p.satisfied);
 setup::configuration::Document a{"x",setup::configuration::Ownership::managed,{{"a","1","old"}}},b{"x",setup::configuration::Ownership::managed,{{"a","2","desired"},{"b","3","desired"}}}; auto d=setup::configuration::diff(a,b);assert(d.set.size()==2);
 setup::profile::Input in;in.discovered["gpu"]="nvidia";in.preferences["shell"]="fish";in.explicit_values["shell"]="bash";in.policy["secure"]="true";auto pr=setup::profile::derive(in);assert(pr.values["shell"]=="bash"&&pr.provenance["secure"]=="policy");
 using namespace runtime::installation::lifecycle;auto rm=plan_removal(Kind::uninstall,{{"/managed",true,false},{"/user",true,true},{"/foreign",false,false}});assert(rm.size()==1&&rm[0].path=="/managed");auto purge=plan_removal(Kind::purge,{{"/user",true,true}});assert(purge.size()==1);
 auto vr=runtime::installation::verification::verify({{"a",[]{return true;}},{"b",[]{return false;}}});assert(!vr.usable&&vr.failed.size()==1);
 auto facts=observation::installation::discover();assert(!facts.facts.empty());
 std::cout<<"SATURATION_IV_PASS\n";
}
