#include "control/reconciliation/semantic/domain_projection.hpp"
#include "domains/services/model.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
struct O: control::reconciliation::pipeline::Observer { std::optional<control::reconciliation::pipeline::Observation> observe(const std::string& id) override { return control::reconciliation::pipeline::Observation{{id,"service",{{"active_state","active"}},{{"systemd","systemd","active",{}}}},true}; }};
int main(){ O o; control::reconciliation::semantic::SemanticObserver s{o,domains::services::model_from}; auto x=s.observe("svc:sshd"); assert(x); assert(s.last_model()); assert(s.last_model()->resource.identity.native_authority=="systemd"); assert(domains::common::affords(*s.last_model(),"start")); std::cout<<"SEMANTIC_PROJECTION_PASS\n"; }
