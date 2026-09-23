#pragma once
#include <chrono>
#include <map>
#include <optional>
#include <shared_mutex>
#include <string>
#include <vector>
namespace rebuntu::model {
struct Fact { std::string subject,predicate,value,source; double confidence{1.0}; std::chrono::system_clock::time_point observed_at{std::chrono::system_clock::now()}; };
class StateStore { public: void upsert(Fact); std::optional<Fact> get(const std::string&,const std::string&) const; std::vector<Fact> subject(const std::string&) const; std::vector<Fact> all() const; std::uint64_t generation() const; private: mutable std::shared_mutex mu_; std::map<std::pair<std::string,std::string>,Fact> facts_; std::uint64_t generation_{}; };
}
