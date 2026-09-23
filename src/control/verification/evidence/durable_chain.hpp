#pragma once
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
namespace rebuntu::control::verification::evidence {
struct DurableEvidenceRecord {
 std::size_t sequence{0}; std::string transaction; std::size_t checkpoint_sequence{0};
 std::string operation; std::string predicate; std::string observed; bool passed{false};
 std::string previous_digest; std::string digest;
};
class DurableEvidenceChain {
 std::filesystem::path path_;
 static void valid(std::string_view s){if(s.find_first_of("\t\n\r")!=std::string_view::npos)throw std::invalid_argument("invalid evidence field");}
 static std::string digest(std::string_view s){std::uint64_t h=1469598103934665603ULL;for(unsigned char c:s){h^=c;h*=1099511628211ULL;}std::ostringstream o;o<<std::hex<<std::setw(16)<<std::setfill('0')<<h;return o.str();}
 static std::string payload(const DurableEvidenceRecord&r){return std::to_string(r.sequence)+'\t'+r.transaction+'\t'+std::to_string(r.checkpoint_sequence)+'\t'+r.operation+'\t'+r.predicate+'\t'+r.observed+'\t'+(r.passed?"1":"0")+'\t'+r.previous_digest;}
 static void sync_parent(const std::filesystem::path& p){auto parent=p.parent_path();if(parent.empty())parent=".";int fd=::open(parent.c_str(),O_RDONLY|O_DIRECTORY);if(fd<0)throw std::runtime_error("evidence directory open failed");if(::fsync(fd)!=0){::close(fd);throw std::runtime_error("evidence directory fsync failed");}::close(fd);}
 static std::vector<std::string> fields(const std::string& line){std::vector<std::string> f;std::size_t p=0;for(;;){auto n=line.find('\t',p);f.push_back(line.substr(p,n-p));if(n==std::string::npos)break;p=n+1;}return f;}
public:
 explicit DurableEvidenceChain(std::filesystem::path p):path_(std::move(p)){}
 const std::filesystem::path& path()const noexcept{return path_;}
 std::vector<DurableEvidenceRecord> load(bool tolerate_torn_tail=false)const{
  std::vector<DurableEvidenceRecord> out;std::ifstream in(path_,std::ios::binary);if(!in){if(!std::filesystem::exists(path_))return out;throw std::runtime_error("evidence read failed");}
  std::string content((std::istreambuf_iterator<char>(in)),{});const bool torn=!content.empty()&&content.back()!='\n';std::size_t pos=0,expected=0;std::string prev;
  while(pos<content.size()){
   auto end=content.find('\n',pos);if(end==std::string::npos){if(tolerate_torn_tail&&torn)break;throw std::runtime_error("torn evidence tail");}
   auto line=content.substr(pos,end-pos);pos=end+1;auto f=fields(line);if(f.size()!=9)throw std::runtime_error("malformed evidence chain");
   DurableEvidenceRecord r;std::size_t used=0;r.sequence=std::stoull(f[0],&used);if(used!=f[0].size()||r.sequence!=expected++)throw std::runtime_error("evidence sequence violation");
   r.transaction=f[1];used=0;r.checkpoint_sequence=std::stoull(f[2],&used);if(used!=f[2].size())throw std::runtime_error("invalid evidence checkpoint sequence");r.operation=f[3];r.predicate=f[4];r.observed=f[5];if(f[6]!="0"&&f[6]!="1")throw std::runtime_error("invalid evidence result");r.passed=f[6]=="1";r.previous_digest=f[7];r.digest=f[8];if(r.previous_digest!=prev||digest(payload(r))!=r.digest)throw std::runtime_error("evidence chain integrity failure");prev=r.digest;out.push_back(std::move(r));
  }return out;
 }
 bool recover_torn_tail()const{
  if(!std::filesystem::exists(path_)) return false;
  std::ifstream in(path_,std::ios::binary);
  std::string content((std::istreambuf_iterator<char>(in)),{});
  if(content.empty()||content.back()=='\n') return false;
  (void)load(true);auto last=content.rfind('\n');std::uintmax_t keep=last==std::string::npos?0:static_cast<std::uintmax_t>(last+1);std::filesystem::resize_file(path_,keep);int fd=::open(path_.c_str(),O_RDWR);if(fd<0)throw std::runtime_error("evidence recovery open failed");if(::fsync(fd)!=0){::close(fd);throw std::runtime_error("evidence recovery fsync failed");}::close(fd);sync_parent(path_);return true;
 }
 DurableEvidenceRecord append(DurableEvidenceRecord r)const{
  auto old=load();r.sequence=old.size();r.previous_digest=old.empty()?std::string{}:old.back().digest;valid(r.transaction);valid(r.operation);valid(r.predicate);valid(r.observed);r.digest=digest(payload(r));auto parent=path_.parent_path();if(!parent.empty())std::filesystem::create_directories(parent);int fd=::open(path_.c_str(),O_WRONLY|O_CREAT|O_APPEND,0600);if(fd<0)throw std::runtime_error("evidence open failed");auto line=payload(r)+'\t'+r.digest+'\n';std::size_t off=0;while(off<line.size()){auto n=::write(fd,line.data()+off,line.size()-off);if(n<=0){::close(fd);throw std::runtime_error("evidence write failed");}off+=static_cast<std::size_t>(n);}if(::fsync(fd)!=0){::close(fd);throw std::runtime_error("evidence fsync failed");}::close(fd);sync_parent(path_);return r;
 }
};
}
