#pragma once
#include <chrono>
#include <map>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::observation {
enum class Quality { unknown, partial, observed, authoritative }; struct Provenance{std::string provider;Quality quality{Quality::unknown};std::chrono::system_clock::time_point observed_at{std::chrono::system_clock::now()};};
struct Observation{std::string domain,key,value;Provenance provenance;}; struct Change{Observation before,after;std::chrono::system_clock::time_point at;};
class StateView {public:void observe(Observation);std::optional<Observation> get(std::string_view domain,std::string_view key)const;std::vector<Observation> domain(std::string_view)const;std::vector<Change> history()const{return history_;}bool fresh(std::string_view,std::string_view,std::chrono::seconds)const;private:std::map<std::string,Observation> current_;std::vector<Change>history_;};
std::vector<Observation> observe_procfs(); std::vector<Observation> observe_filesystem(std::string_view path="/");
}