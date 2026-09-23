#include <domains/software/dpkg.hpp>
#include <fstream>
#include <map>
namespace rebuntu::domains::package {
bool Package::installed()const{return status=="install ok installed";}
std::vector<Package>DpkgStatus::all()const{std::ifstream f(path_);std::vector<Package>out;std::map<std::string,std::string>m;std::string line,key;auto flush=[&]{if(m.count("Package"))out.push_back({m["Package"],m["Version"],m["Architecture"],m["Status"]});m.clear();key.clear();};while(std::getline(f,line)){if(line.empty()){flush();continue;}if((line[0]==' '||line[0]=='\t')&&!key.empty()){m[key]+="\n"+line.substr(1);continue;}auto p=line.find(':');if(p!=std::string::npos){key=line.substr(0,p);auto v=line.substr(p+1);if(!v.empty()&&v[0]==' ')v.erase(0,1);m[key]=v;}}flush();return out;}
std::optional<Package>DpkgStatus::find(const std::string&n)const{for(auto&p:all())if(p.name==n)return p;return{};}
}
