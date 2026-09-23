#include "domains/storage/reconciliation/storage_controller.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
class FakeFs final: public providers::linux::filesystems::Provider {
public:
 providers::linux::filesystems::MountSnapshot s{"/dev/test","/srv/data","ext4","rw",false};
 std::optional<providers::linux::filesystems::MountSnapshot> observe_mount(std::string_view target) override { if(target!=s.target) return std::nullopt; return s; }
 bool execute(const core::NativeOperation& op) override { if(op.target!=s.target) return false; if(op.verb=="mount") s.mounted=true; else if(op.verb=="unmount") s.mounted=false; else return false; return true; }
};
int main(){ FakeFs fs; domains::storage::reconciliation::StorageController c(fs); core::DesiredState d{"/srv/data",{{"mounted","true"},{"source","/dev/test"},{"filesystem","ext4"}},"required data volume"}; auto preview=c.reconcile(d,false); assert(!preview.converged); auto result=c.reconcile(d,true); assert(result.converged); std::cout<<"STORAGE_RECONCILIATION_PASS\n"; }
