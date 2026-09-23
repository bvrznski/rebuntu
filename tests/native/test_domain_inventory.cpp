#include <domains/storage/inventory.hpp>
#include <domains/networking/inventory.hpp>
#include <domains/accelerators/inventory.hpp>
#include <domains/processes/inventory.hpp>
#include <domains/services/systemd.hpp>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace rebuntu::domains;
static void put(const std::filesystem::path&p,const std::string&s){std::filesystem::create_directories(p.parent_path());std::ofstream(p)<<s;}
int main(){auto root=std::filesystem::temp_directory_path()/"rebuntu-domain-inventory-test";std::filesystem::remove_all(root);auto sys=root/"sys",proc=root/"proc";
 // storage sysfs + mountinfo
 auto b=sys/"class/block/nvme0n1";put(b/"size","2048\n");put(b/"queue/logical_block_size","4096\n");put(b/"queue/rotational","0\n");put(b/"removable","0\n");put(b/"ro","0\n");put(b/"device/model","TEST NVME\n");put(b/"device/vendor","TEST\n");
 put(proc/"self/mountinfo","36 25 259:2 / / rw,relatime - ext4 /dev/nvme0n1p2 rw\n37 36 259:3 / /home rw,relatime - ext4 /dev/nvme0n1p3 rw\n");storage::Inventory si(sys,proc);auto dev=si.block_devices();assert(dev.size()==1&&dev[0].size_bytes==2048ULL*512);auto m=si.mount_for("/home/user/file");assert(m&&m->target=="/home"&&m->filesystem=="ext4");
 // network sysfs + proc route
 auto n=sys/"class/net/eth0";put(n/"operstate","up\n");put(n/"mtu","1500\n");put(n/"address","00:11:22:33:44:55\n");put(n/"statistics/rx_bytes","123\n");put(n/"statistics/tx_bytes","456\n");put(proc/"net/route","Iface Destination Gateway Flags RefCnt Use Metric Mask MTU Window IRTT\neth0 00000000 0102A8C0 0003 0 0 100 00000000 0 0 0\n");network::Inventory ni(sys,proc);auto is=ni.interfaces();assert(is.size()==1&&is[0].up&&is[0].rx_bytes==123);auto rs=ni.ipv4_routes();assert(rs.size()==1&&rs[0].gateway=="192.168.2.1");
 // PCI GPU
 auto g=sys/"bus/pci/devices/0000:0b:00.0";put(g/"vendor","0x10de\n");put(g/"device","0x2204\n");put(g/"class","0x030000\n");std::filesystem::create_directories(sys/"bus/pci/drivers/nvidia");std::filesystem::create_symlink(sys/"bus/pci/drivers/nvidia",g/"driver");gpu::Inventory gi(sys);auto gs=gi.display_devices();assert(gs.size()==1&&gs[0].driver&&*gs[0].driver=="nvidia");
 // proc stat: fields after comm start at state; starttime is item 20 in our tail vector
 auto p=proc/"123";put(p/"stat","123 (worker thread) S 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 5 17 18 424242 20 21\n");put(p/"cmdline",std::string("worker\0--job\0",13));process::Inventory pi(proc);auto ps=pi.get(123);assert(ps&&ps->name=="worker thread"&&ps->ppid==1&&ps->nice==5&&ps->start_ticks==424242);
 auto u=service::parse_systemctl_show("Id=ssh.service\nLoadState=loaded\nActiveState=active\nSubState=running\nUnitFileState=enabled\n");assert(u.id=="ssh.service"&&u.active=="active"&&u.unit_file=="enabled");assert(service::valid_unit_name("ssh.service"));assert(!service::valid_unit_name("../evil.service"));
 std::filesystem::remove_all(root);std::cout<<"domain inventory deepening ok\n";
}
