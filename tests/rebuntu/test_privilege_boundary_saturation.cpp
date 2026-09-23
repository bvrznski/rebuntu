#include "security/privilege-boundary-secure-execution/boundary/secure_boundary.hpp"
#include "security/privilege-boundary-secure-execution/ipc/message_frame.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
using namespace rebuntu::security::privilege_boundary_secure_execution;
int main(){
 SecureBoundary b({128,32,2,64}); PeerIdentity p{1000,1000,42,99}; AuthorizationBinding a{"fp","operator",7,true}; SecureRequest r{"r",OperationKind::ServiceStart,"sshd.service","","fp",7};
 assert(b.validate(r,p,p,a,0).accepted); std::cout<<"PRIVILEGE_TYPED_BOUNDARY_PASS\n";
 auto bad=r; bad.target="../../etc/shadow"; assert(b.validate(bad,p,p,a,0).reason==RejectReason::InvalidTarget); std::cout<<"PRIVILEGE_PATH_TRAVERSAL_REJECTED_PASS\n";
 auto spoof=p; spoof.start_ticks=100; assert(b.validate(r,spoof,p,a,0).reason==RejectReason::PeerMismatch); std::cout<<"PRIVILEGE_PEER_REUSE_REJECTED_PASS\n";
 auto stale=a; stale.generation=6; assert(b.validate(r,p,p,stale,0).reason==RejectReason::StaleAuthorization); std::cout<<"PRIVILEGE_STALE_AUTH_REJECTED_PASS\n";
 auto huge=r; huge.payload=std::string(40,'x'); assert(b.validate(huge,p,p,a,0).reason==RejectReason::Oversize); assert(b.validate(r,p,p,a,2).reason==RejectReason::ResourceExhausted); std::cout<<"PRIVILEGE_RESOURCE_BOUNDS_PASS\n";
 auto red=SecureBoundary::redact_error("token=abc password=hunter2 harmless=x"); assert(red.find("abc")==std::string::npos&&red.find("hunter2")==std::string::npos); std::cout<<"PRIVILEGE_ERROR_REDACTION_PASS\n";
 CancellationRegistry c; assert(c.begin("x")&&c.cancel("x")&&c.cancelled("x")); c.finish("x"); assert(!c.cancelled("x")); std::cout<<"PRIVILEGE_CANCELLATION_PASS\n";
 auto close=descriptors_to_close({0,1,2,7,8,7},{}); assert((close==std::vector<int>{7,8})); std::cout<<"PRIVILEGE_FD_HYGIENE_PASS\n";
 RestartBudget rb(2,std::chrono::seconds(10),std::chrono::milliseconds(100)); auto t=std::chrono::steady_clock::now(); assert(rb.record_crash(t)); assert(rb.backoff()==std::chrono::milliseconds(100)); assert(rb.record_crash(t)); assert(rb.backoff()==std::chrono::milliseconds(200)); assert(!rb.record_crash(t)); std::cout<<"PRIVILEGE_RESTART_BUDGET_PASS\n";
 MessageFramer mf(8); MessageFrame f{1,3,{std::byte{1},std::byte{2}}}; auto enc=mf.encode(f); assert(enc); auto dec=mf.decode(*enc); assert(dec&&dec->type==3&&dec->payload.size()==2); auto corrupt=*enc; corrupt[7]=std::byte{9}; assert(!mf.decode(corrupt)); std::cout<<"PRIVILEGE_BOUNDED_FRAMING_PASS\n";
}
