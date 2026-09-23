#include "../../src/domains/processes/reconciliation/process_controller.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
class Fake final: public providers::linux::procfs::ProcessProvider {
public:
 std::optional<providers::linux::procfs::ProcessSnapshot> state=providers::linux::procfs::ProcessSnapshot{42,1,1234,"worker","R",{"worker"}};
 std::optional<providers::linux::procfs::ProcessSnapshot> observe(int) override { return state; }
 bool execute(const core::NativeOperation& op) override { if(op.arguments.at("start_ticks")!="1234") return false; if(op.verb=="terminate") state.reset(); return true; }
};
int main(){ Fake f; domains::processes::reconciliation::ProcessController c(f); core::DesiredState d{"process:42",{{"state","stopped"}},"operator intent"}; auto p=c.plan(d,c.observe(42)); assert(p.operations.size()==1); assert(p.operations[0].arguments.at("start_ticks")=="1234"); auto v=c.reconcile(42,d,true); assert(v.converged); std::cout<<"PROCESS_RECONCILIATION_PASS\n"; }
