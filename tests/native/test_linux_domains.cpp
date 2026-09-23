#include <domains/linux_domains.hpp>
#include <automation/orchestration/domain_runtime.hpp>
#include <semantics/entities/state_store.hpp>
#include <runtime/state/persistence/journal.hpp>
#include <security/policy/policy_engine.hpp>
#include <observation/telemetry/telemetry.hpp>
#include <cassert>
#include <filesystem>
#include <iostream>
int main(){using namespace rebuntu;domains::LinuxDomainRegistry registry;
 auto svc=registry.get(management::Domain::service).plan({management::Domain::service,"ssh.service","state","active"},std::string("inactive"));assert(svc.command.program=="systemctl");assert(svc.verify&&svc.rollback);
 auto net=registry.get(management::Domain::network).plan({management::Domain::network,"eth0","link","up"},std::string("down"));assert(net.command.program=="ip");
 auto pkg=registry.get(management::Domain::package).plan({management::Domain::package,"curl","install","true"},std::nullopt);assert(pkg.command.program=="apt-get");
 auto path=std::filesystem::temp_directory_path()/"rebuntu-domain-runtime.journal";std::filesystem::remove(path);model::StateStore state;policy::PolicyEngine policy;backend::DryRunBackend backend;persistence::Journal journal(path);telemetry::Telemetry telemetry;orchestration::DomainRuntime runtime(state,policy,backend,journal,telemetry,registry);
 auto denied=runtime.apply({management::Domain::service,"ssh.service","enabled","true"},false,true);assert(!denied.executed);
 auto ok=runtime.apply({management::Domain::service,"ssh.service","enabled","true"},true,true);assert(ok.executed&&ok.verified);assert(state.get("ssh.service","enabled")->value=="true");assert(backend.commands().size()==2);
 auto probes=runtime.inspect(management::Domain::gpu,"0");assert(probes.count("gpu")==1);assert(backend.commands().back().program=="nvidia-smi");std::filesystem::remove(path);std::cout<<"linux domain backends ok\n";}
