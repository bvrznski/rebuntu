#include "../../src/domains/services/reconciliation/service_controller.hpp"
#include "../../src/security/policy/operation_policy.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
class FakeSystemd: public providers::linux::systemd::Provider { public: providers::linux::systemd::UnitSnapshot s{"demo.service","loaded","inactive","dead","disabled"}; std::optional<providers::linux::systemd::UnitSnapshot> observe(std::string_view) override{return s;} bool execute(const core::NativeOperation& op) override { if(op.verb=="start"){s.active_state="active";s.sub_state="running";} else if(op.verb=="enable")s.unit_file_state="enabled"; else return false; return true;} };
int main(){ FakeSystemd f; domains::services::reconciliation::ServiceController c(f); core::DesiredState d{"demo.service",{{"active_state","active"},{"unit_file_state","enabled"}},"test"}; auto before=c.observe("demo.service"); auto p=c.plan(d,before); assert(p.operations.size()==2); security::policy::OperationPolicy policy({"systemd:start","systemd:enable"}); for(auto& op:p.operations) assert(policy.permits(op)); auto v=c.reconcile(d,true); assert(v.converged); std::cout<<"REBUNTU_SERVICE_RECONCILIATION_PASS\n"; }
