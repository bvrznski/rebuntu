#include <domains/networking/inventory.hpp>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
namespace rebuntu::domains::network {
static std::string read(const std::filesystem::path&p){std::ifstream f(p);std::string s;std::getline(f,s);return s;}static std::uint64_t n(const std::filesystem::path&p){try{return std::stoull(read(p));}catch(...){return 0;}}
std::vector<Interface> Inventory::interfaces()const{std::vector<Interface> out;auto root=sys_/"class/net";if(!std::filesystem::exists(root))return out;for(auto&e:std::filesystem::directory_iterator(root)){Interface i;i.name=e.path().filename();i.operstate=read(e.path()/"operstate");i.up=i.operstate=="up";i.mtu=n(e.path()/"mtu");i.rx_bytes=n(e.path()/"statistics/rx_bytes");i.tx_bytes=n(e.path()/"statistics/tx_bytes");auto a=read(e.path()/"address");if(!a.empty())i.address=a;out.push_back(std::move(i));}std::sort(out.begin(),out.end(),[](auto&a,auto&b){return a.name<b.name;});return out;}
static std::string ip(std::string h){try{uint32_t v=std::stoul(h,nullptr,16);in_addr a{v};char b[INET_ADDRSTRLEN]{};return inet_ntop(AF_INET,&a,b,sizeof b)?b:"";}catch(...){return "";}}
std::vector<Route> Inventory::ipv4_routes()const{std::ifstream f(proc_/"net/route");std::vector<Route> out;std::string line;std::getline(f,line);while(std::getline(f,line)){std::istringstream s(line);std::string iface,dst,gw,flags;if(!(s>>iface>>dst>>gw>>flags))continue;Route r;r.interface=iface;r.destination=ip(dst);r.gateway=ip(gw);try{r.flags=std::stoul(flags,nullptr,16);}catch(...){}out.push_back(std::move(r));}return out;}
}
