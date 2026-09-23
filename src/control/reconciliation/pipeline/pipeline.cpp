#include "pipeline.hpp"
namespace rebuntu::control::reconciliation::pipeline {
Result Pipeline::reconcile(const core::DesiredState& desired, bool apply) {
  Result out; out.trace.push_back("observe");
  auto observed = observer_.observe(desired.entity_id);
  if (!observed || !observed->authoritative) { out.trace.push_back("observation-unavailable"); return out; }
  out.trace.push_back("verify-before");
  out.verification = verifier_.verify(desired, observed->entity);
  if (out.verification.converged) { out.status=Result::Status::converged; return out; }
  out.trace.push_back("plan"); out.plan=planner_.synthesize(desired, observed->entity);
  out.trace.push_back("authorize"); auto decision=policy_.authorize(out.plan, observed->entity);
  if (!decision.allowed) { out.status=Result::Status::blocked; out.trace.insert(out.trace.end(), decision.reasons.begin(), decision.reasons.end()); return out; }
  if (!apply) { out.status=Result::Status::planned; out.trace.push_back("dry-run"); return out; }
  for (const auto& op: out.plan.operations) {
    if (!op.mutating) continue;
    out.trace.push_back("execute:"+op.provider+":"+op.verb);
    if (!executor_.execute(op)) { out.trace.push_back("execution-failed"); return out; }
  }
  out.trace.push_back("re-observe"); auto after=observer_.observe(desired.entity_id);
  if (!after || !after->authoritative) { out.trace.push_back("post-observation-unavailable"); return out; }
  out.trace.push_back("verify-after"); out.verification=verifier_.verify(desired, after->entity);
  out.status=out.verification.converged ? Result::Status::applied : Result::Status::failed;
  return out;
}
}
