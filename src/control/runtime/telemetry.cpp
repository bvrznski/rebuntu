#include <observation/telemetry/telemetry.hpp>
#include <algorithm>
namespace rebuntu::telemetry {
void Telemetry::record(Event e){
    if(e.at.time_since_epoch().count()==0)e.at=std::chrono::system_clock::now();
    std::scoped_lock lock(mutex_); auto& c=counters_[{e.subsystem,e.operation}]; ++c.attempts; if(e.success)++c.successes;else ++c.failures; c.total_latency+=e.latency; events_.push_back(std::move(e)); if(events_.size()>4096)events_.erase(events_.begin(),events_.begin()+1024);
}
Counter Telemetry::counter(const std::string&s,const std::string&o)const{std::scoped_lock lock(mutex_);auto it=counters_.find({s,o});return it==counters_.end()?Counter{}:it->second;}
std::vector<Event> Telemetry::recent(std::size_t n)const{std::scoped_lock lock(mutex_);n=std::min(n,events_.size());return {events_.end()-static_cast<std::ptrdiff_t>(n),events_.end()};}
std::vector<Event> Telemetry::for_target(const std::string&t,std::size_t n)const{std::scoped_lock lock(mutex_);std::vector<Event> out;for(auto it=events_.rbegin();it!=events_.rend()&&out.size()<n;++it)if(it->target==t)out.push_back(*it);std::reverse(out.begin(),out.end());return out;}
}
