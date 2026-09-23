#include "domains/common/operations/synthesis.hpp"
#include "domains/common/requirements/resolution.hpp"
#include "domains/common/health/aggregation.hpp"
#include "domains/services/model.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
int main(){ core::Entity e{"svc:sshd","service",{{"active_state","inactive"}}, {}}; auto m=domains::services::model_from(e); domains::common::DesiredResourceState d{e.id,{{"active_state","active"}},"availability"};
 auto s=domains::common::operations::synthesize(d,m,{{"active_state","active","start","systemd",true},{"active_state","inactive","stop","systemd",true}}); assert(s.unsupported.empty()); assert(s.plan.operations.size()==1); assert(s.plan.operations[0].provider=="systemd"); assert(s.plan.operations[0].verb=="start");
 m.requirements={{"active_state","inactive",true}}; auto rr=domains::common::requirements::resolve(m,{"start"}); assert(rr.ready()); auto rr2=domains::common::requirements::resolve(m,{"mount"}); assert(!rr2.ready());
 assert(domains::common::health::aggregate(m.health)==domains::common::health::Status::unknown); std::cout<<"DOMAIN_SYNTHESIS_PASS\n"; }
