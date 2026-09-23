#pragma once
#include "model.hpp"
namespace rebuntu::domains::common {
struct DomainProfile { std::string kind; std::string authority; std::vector<Capability> capabilities; };
inline DomainProfile service_profile(){ return {"service","systemd",{{"lifecycle",{"start","stop","restart"},{}},{"enablement",{"enable","disable"},{}}}}; }
inline DomainProfile process_profile(){ return {"process","linux-kernel/procfs",{{"lifecycle",{"terminate","continue"},{}},{"priority",{"renice"},{}}}}; }
inline DomainProfile storage_profile(){ return {"storage","linux-kernel/filesystems",{{"availability",{"mount","unmount"},{}},{"capacity",{"inspect"},{}}}}; }
inline DomainProfile networking_profile(){ return {"network","linux-kernel/netlink",{{"link",{"up","down"},{}},{"addressing",{"add_address","remove_address"},{}}}}; }
inline DomainProfile software_profile(){ return {"package","native-package-manager",{{"package",{"install","remove","upgrade"},{}}}}; }
inline DomainProfile configuration_profile(){ return {"configuration","filesystem/native-owner",{{"configuration",{"write","restore"},{}}}}; }
inline DomainProfile identity_profile(){ return {"identity","NSS/PAM",{{"identity",{"observe"},{}}}}; }
inline DomainProfile accelerator_profile(){ return {"accelerator","linux-driver/sysfs",{{"compute",{"inspect","place_workload"},{}}}}; }
inline DomainModel build_model(const core::Entity& e,const DomainProfile& p){ DomainModel m; m.resource=project(e,p.authority); m.capabilities=p.capabilities; return m; }
}
