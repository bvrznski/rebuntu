#include <control/homeostasis/contracts.hpp>
#include <algorithm>
#include <cctype>
#include <functional>
namespace rebuntu::stability {
static int rank(Severity s){return static_cast<int>(s);} static std::string lower(std::string s){std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){return std::tolower(c);});return s;}
void StabilityService::ingest(Event e){ auto a=analyze(e); events_.push_back(std::move(e)); while(events_.size()>max_events_)events_.pop_front(); if(a){auto [it,n]=alerts_.try_emplace(a->id,*a); if(!n)++it->second.occurrences;}}
void StabilityService::add_fact(Fact f){facts_[f.key]=std::move(f);} std::optional<Alert> StabilityService::analyze(const Event&e)const{return HealthClassifier::classify(e);}
Snapshot StabilityService::snapshot()const{Snapshot s; for(auto&[k,v]:facts_)s.facts.push_back(v); s.events.assign(events_.begin(),events_.end()); for(auto&[k,v]:alerts_)s.alerts.push_back(v); return s;}
std::vector<Event> StabilityService::filter(std::string_view d,Severity m)const{std::vector<Event>o;for(auto&e:events_)if((d.empty()||e.domain==d)&&rank(e.severity)>=rank(m))o.push_back(e);return o;}
void StabilityService::acknowledge(std::string_view id){auto i=alerts_.find(std::string(id));if(i!=alerts_.end())i->second.acknowledged=true;}
Event JournalNormalizer::normalize(std::string_view l){Event e; e.source="journald";e.domain="system";e.message=std::string(l);auto x=lower(e.message);if(x.find("critical")!=std::string::npos||x.find("panic")!=std::string::npos)e.severity=Severity::critical;else if(x.find("error")!=std::string::npos||x.find("failed")!=std::string::npos)e.severity=Severity::error;else if(x.find("warn")!=std::string::npos)e.severity=Severity::warning;return e;}
std::optional<Alert> HealthClassifier::classify(const Event&e){if(rank(e.severity)<rank(Severity::warning))return{};auto m=lower(e.message);std::string kind="system";if(m.find("gpu")!=std::string::npos||m.find("nvidia")!=std::string::npos)kind="gpu";else if(m.find("oom")!=std::string::npos||m.find("memory")!=std::string::npos)kind="memory";else if(m.find("filesystem")!=std::string::npos||m.find("i/o error")!=std::string::npos)kind="storage";else if(m.find("hung")!=std::string::npos||m.find("stall")!=std::string::npos)kind="stall";return Alert{kind+"-health",kind+" health event",e.message,e.severity};}
}