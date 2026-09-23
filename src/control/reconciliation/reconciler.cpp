#include "reconciler.hpp"
namespace rebuntu::control::reconciliation {
Cycle run(Observe observe,Plan planner,Apply apply,Verify verify,bool execute){ Cycle c; c.before=observe(); c.plan=planner(c.before); if(execute) for(auto& op:c.plan.operations) if(!apply(op)) return {c.before,c.plan,{false,{"operation failed: "+op.verb},{}}}; auto after=observe(); c.after=verify(after); return c; }
}
