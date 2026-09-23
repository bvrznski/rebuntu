#include <domains/configuration/atomic_file.hpp>
#include <domains/software/dpkg.hpp>
#include <domains/identity/passwd.hpp>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <unistd.h>
int main(){namespace fs=std::filesystem;auto root=fs::temp_directory_path()/ ("rebuntu-deep-"+std::to_string(getpid()));fs::create_directories(root);
 auto cfg=root/"etc/app.conf";auto a=rebuntu::domains::configuration::AtomicFile::replace(cfg,"a=1\n");assert(a.changed);auto b=rebuntu::domains::configuration::AtomicFile::replace(cfg,"a=1\n");assert(!b.changed);auto c=rebuntu::domains::configuration::AtomicFile::replace(cfg,"a=2\n");assert(c.changed&&c.backup&&fs::exists(*c.backup));assert(rebuntu::domains::configuration::AtomicFile::read(*c.backup)=="a=1\n");
 auto dp=root/"status";std::ofstream(dp)<<"Package: alpha\nStatus: install ok installed\nArchitecture: amd64\nVersion: 1.2.3\n\nPackage: beta\nStatus: deinstall ok config-files\nArchitecture: all\nVersion: 2\n";rebuntu::domains::package::DpkgStatus db(dp);assert(db.all().size()==2);assert(db.find("alpha")->installed());assert(!db.find("beta")->installed());
 auto pw=root/"passwd";std::ofstream(pw)<<"root:x:0:0:root:/root:/bin/bash\nalice:x:1000:1000:Alice:/home/alice:/usr/bin/fish\nmalformed\n";rebuntu::domains::identity::PasswdDatabase pdb(pw);assert(pdb.all().size()==2);assert(pdb.find("alice")->uid==1000);assert(pdb.find((uid_t)0)->name=="root");fs::remove_all(root);}
