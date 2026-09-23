#include <control/recovery/recovery.hpp>
namespace rebuntu::recovery {
RecoveryResult RecoveryCoordinator::rollback_target(const std::string&t){auto e=journal_.latest(t);if(!e)return {false,"no journal entry"};if(e->before_value.empty())return {false,"no recoverable previous value"};backend::Command c{"rebuntu-backend-restore",{e->domain,e->target,e->action,e->before_value},true};auto r=backend_.execute(c);bool ok=r.exit_code==0&&!r.timed_out;telemetry_.record({{},"recovery","rollback",t,ok,{},{{"transaction",e->transaction_id}}});if(ok)journal_.append({e->transaction_id+"-rollback",e->domain,e->target,e->action,e->after_value,e->before_value,"rolled_back"});return {ok,ok?"rollback applied":r.stderr_text};}
}
