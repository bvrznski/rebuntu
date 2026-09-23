#include <domains/identity/passwd.hpp>
#include <fstream>
#include <sstream>
namespace rebuntu::domains::identity {
std::vector<User>PasswdDatabase::all()const{std::ifstream f(path_);std::vector<User>o;std::string l;while(std::getline(f,l)){std::vector<std::string>x;std::stringstream s(l);std::string q;while(std::getline(s,q,':'))x.push_back(q);if(x.size()!=7)continue;try{o.push_back({x[0],static_cast<uid_t>(std::stoul(x[2])),static_cast<gid_t>(std::stoul(x[3])),x[4],x[5],x[6]});}catch(...){}}return o;}
std::optional<User>PasswdDatabase::find(const std::string&n)const{for(auto&u:all())if(u.name==n)return u;return{};}std::optional<User>PasswdDatabase::find(uid_t id)const{for(auto&u:all())if(u.uid==id)return u;return{};}
}
