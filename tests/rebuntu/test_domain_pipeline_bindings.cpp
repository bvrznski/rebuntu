#include "control/reconciliation/bindings/domain_bindings.hpp"
#include <cassert>
#include <iostream>
using namespace rebuntu;
namespace b=control::reconciliation::bindings; namespace p=control::reconciliation::pipeline;
struct Sys final: providers::linux::systemd::Provider { providers::linux::systemd::UnitSnapshot s{"demo.service","loaded","inactive","dead","disabled"}; std::optional<providers::linux::systemd::UnitSnapshot> observe(std::string_view) override{return s;} bool execute(const core::NativeOperation&o)override{if(o.verb=="start")s.active_state="active"; if(o.verb=="enable")s.unit_file_state="enabled"; return true;} };
struct Proc final: providers::linux::procfs::ProcessProvider { providers::linux::procfs::ProcessSnapshot s{42,1,77,"demo","T",{}}; std::optional<providers::linux::procfs::ProcessSnapshot> observe(int pid)override{if(pid!=42)return std::nullopt;return s;} bool execute(const core::NativeOperation&o)override{if(o.verb=="continue")s.state="R";return true;} };
struct Fs final: providers::linux::filesystems::Provider { std::optional<providers::linux::filesystems::MountSnapshot> s; std::optional<providers::linux::filesystems::MountSnapshot> observe_mount(std::string_view)override{return s;} bool execute(const core::NativeOperation&o)override{if(o.verb=="mount")s=providers::linux::filesystems::MountSnapshot{o.arguments.at("source"),o.target,o.arguments.at("filesystem"),o.arguments.contains("options")?o.arguments.at("options"):"",true};return true;} };
int main(){ b::AllowPolicy policy;
 {Sys native; b::ServiceBinding x(native); p::Pipeline pipe(x,x,policy,x,x); core::DesiredState d{"demo.service",{{"active_state","active"},{"unit_file_state","enabled"}},"test"}; auto r=pipe.reconcile(d,true); assert(r.status==p::Result::Status::applied);}
 {Proc native; b::ProcessBinding x(native); p::Pipeline pipe(x,x,policy,x,x); core::DesiredState d{"process:42",{{"state","running"}},"test"}; auto r=pipe.reconcile(d,true); assert(r.status==p::Result::Status::applied);}
 {Fs native; b::StorageBinding x(native); p::Pipeline pipe(x,x,policy,x,x); core::DesiredState d{"/mnt/demo",{{"mounted","true"},{"source","/dev/mock"},{"filesystem","ext4"}},"test"}; auto r=pipe.reconcile(d,true); assert(r.status==p::Result::Status::applied);}
 std::cout<<"DOMAIN_PIPELINE_BINDINGS_PASS\n"; }
