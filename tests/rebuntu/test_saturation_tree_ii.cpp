#include "core/state/state_machine.hpp"
#include "core/evidence/evidence_store.hpp"
#include "core/verification/verification_report.hpp"
#include "core/transactions/journal.hpp"
#include <cassert>
#include <iostream>
int main(){
 rebuntu::core::state::StateMachine sm("observed"); sm.allow("observed","planned"); assert(sm.transition_to("planned")); assert(!sm.transition_to("committed"));
 rebuntu::core::evidence::Store es; es.append({"svc:a","systemd","systemd","active",{}}); assert(es.for_subject("svc:a").size()==1);
 rebuntu::core::verification::Report vr; vr.add({"desired-state",true,"observed"}); assert(vr.converged()); vr.add({"policy",false,"denied"}); assert(!vr.converged());
 rebuntu::core::transactions::Journal j; j.advance(rebuntu::core::transactions::Stage::executing,"execute"); j.advance(rebuntu::core::transactions::Stage::verifying,"verify"); j.advance(rebuntu::core::transactions::Stage::committed,"commit"); assert(j.entries().size()==4);
 std::cout<<"TREE_DEEPENING_II_SATURATION_PASS\n";
}
