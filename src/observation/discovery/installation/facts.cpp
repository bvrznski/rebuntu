#include "facts.hpp"
#include <sys/utsname.h>
#include <fstream>
#include <unistd.h>
namespace rebuntu::observation::installation {
Snapshot discover(){Snapshot s;auto now=std::chrono::system_clock::now();struct utsname u{};if(uname(&u)==0){s.facts.push_back({"kernel.arch",u.machine,"uname",now});s.facts.push_back({"kernel.release",u.release,"uname",now});}else s.warnings.push_back("uname unavailable"); std::ifstream m("/proc/meminfo");std::string k,v,unit;if(m>>k>>v>>unit)s.facts.push_back({"memory.memtotal_kib",v,"procfs:/proc/meminfo",now}); if(access("/run/systemd/system",F_OK)==0)s.facts.push_back({"init.systemd","true","filesystem:/run/systemd/system",now}); return s;}
}
