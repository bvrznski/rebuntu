#include "secure_boundary.hpp"
#include <algorithm>
#include <cctype>
#include <limits>

namespace rebuntu::security::privilege_boundary_secure_execution {
SecureBoundary::SecureBoundary(BoundaryLimits l):limits_(l){}
bool SecureBoundary::safe_target(std::string_view s) noexcept {
 if(s.empty() || s.size()>4096 || s.front()=='/' || s.find("..")!=std::string_view::npos || s.find('\0')!=std::string_view::npos) return false;
 for(unsigned char c: s) if(!(std::isalnum(c)||c=='_'||c=='-'||c=='.'||c=='@'||c==':'||c=='/')) return false;
 return true;
}
ValidationResult SecureBoundary::validate(const SecureRequest& r,const PeerIdentity& peer,const PeerIdentity& expected,const AuthorizationBinding& a,std::size_t inflight) const {
 auto reject=[](RejectReason x,std::string m){return ValidationResult{false,x,std::move(m)};};
 if(inflight>=limits_.max_inflight) return reject(RejectReason::ResourceExhausted,"privileged boundary busy");
 if(r.target.size()>limits_.max_target_bytes || !safe_target(r.target)) return reject(RejectReason::InvalidTarget,"invalid operation target");
 if(r.payload.size()>limits_.max_payload_bytes || r.request_id.size()+r.target.size()+r.payload.size()+r.operation_fingerprint.size()>limits_.max_message_bytes) return reject(RejectReason::Oversize,"request exceeds boundary limits");
 if(peer.uid!=expected.uid || peer.gid!=expected.gid || peer.pid!=expected.pid || peer.start_ticks!=expected.start_ticks) return reject(RejectReason::PeerMismatch,"caller identity mismatch");
 if(!a.allowed || a.operation_fingerprint.empty() || a.operation_fingerprint!=r.operation_fingerprint) return reject(RejectReason::MissingAuthorization,"operation not authorized");
 if(a.generation!=r.authorization_generation) return reject(RejectReason::StaleAuthorization,"authorization is stale");
 return {true,RejectReason::None,{}};
}
std::string SecureBoundary::redact_error(std::string_view in){
 std::string out(in); const std::vector<std::string> keys={"password=","token=","secret=","authorization="};
 std::string lower=out; std::transform(lower.begin(),lower.end(),lower.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
 for(const auto& k:keys){ std::size_t p=0; while((p=lower.find(k,p))!=std::string::npos){auto b=p+k.size(),e=out.find_first_of(" \t\r\n;&",b); if(e==std::string::npos)e=out.size(); out.replace(b,e-b,"<redacted>"); lower=out; std::transform(lower.begin(),lower.end(),lower.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));}); p=b+10; }}
 return out;
}
bool CancellationRegistry::begin(std::string id){return requests_.emplace(std::move(id),false).second;}
bool CancellationRegistry::cancel(std::string_view id){auto it=requests_.find(std::string(id)); if(it==requests_.end())return false; it->second=true; return true;}
bool CancellationRegistry::cancelled(std::string_view id)const{auto it=requests_.find(std::string(id)); return it!=requests_.end()&&it->second;}
void CancellationRegistry::finish(std::string_view id){requests_.erase(std::string(id));}
RestartBudget::RestartBudget(std::size_t m,std::chrono::milliseconds w,std::chrono::milliseconds b):max_(m),window_(w),base_(b){}
bool RestartBudget::record_crash(std::chrono::steady_clock::time_point now){crashes_.erase(std::remove_if(crashes_.begin(),crashes_.end(),[&](auto t){return now-t>window_;}),crashes_.end()); crashes_.push_back(now); ++consecutive_; return crashes_.size()<=max_;}
std::chrono::milliseconds RestartBudget::backoff()const noexcept{std::size_t shift=std::min<std::size_t>(consecutive_?consecutive_-1:0,10); auto mult=std::uint64_t{1}<<shift; auto n=static_cast<std::uint64_t>(base_.count()); if(n>static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max())/mult) return std::chrono::milliseconds::max(); return base_*static_cast<std::int64_t>(mult);}
void RestartBudget::record_healthy(){consecutive_=0; crashes_.clear();}
std::vector<int> descriptors_to_close(const std::vector<int>& fds,const FdPolicy& p){std::vector<int> out; if(!p.close_unknown)return out; for(int fd:fds)if(fd>=0&&!p.allowed.contains(fd))out.push_back(fd); std::sort(out.begin(),out.end()); out.erase(std::unique(out.begin(),out.end()),out.end()); return out;}
}
