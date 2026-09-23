#include "domains/common/model.hpp"
#include "domains/common/profiles.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
int main(){
 core::Entity e{"svc:sshd","service",{{"active_state","active"}},{{"systemd","systemd","active",{}}}};
 auto m=domains::common::build_model(e,domains::common::service_profile());
 assert(m.resource.identity.native_authority=="systemd"); assert(domains::common::affords(m,"restart")); assert(!domains::common::affords(m,"mount"));
 domains::common::DesiredResourceState d{"svc:sshd",{{"active_state","active"}},"keep available"};
 assert(domains::common::verify(d,m.resource).converged); d.attributes["active_state"]="inactive"; assert(!domains::common::verify(d,m.resource).converged);
 m.requirements={{"active_state","active",true}}; assert(domains::common::evaluate(m.resource,m.requirements).satisfied);
 domains::common::Topology t; assert(t.add(m.resource)); core::Entity p{"pid:1","process",{}, {}}; assert(t.add(domains::common::project(p,"linux-kernel/procfs"))); assert(t.link({"svc:sshd","controls","pid:1",{}}));
 domains::common::HealthSignal hs{"availability","ok","observed",{"systemd","systemd","active",{}}}; m.health.signals.push_back(hs); assert(m.health.healthy());
 std::cout<<"DOMAIN_SEMANTIC_MODELS_PASS\n";
}
