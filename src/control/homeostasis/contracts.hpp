#pragma once
#include <chrono>
#include <deque>
#include <map>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::stability {
enum class Severity { debug, info, notice, warning, error, critical };
enum class EvidenceQuality { unknown, inferred, observed, authoritative };
struct Event { std::string source, domain, message; Severity severity{Severity::info}; std::chrono::system_clock::time_point at{std::chrono::system_clock::now()}; std::map<std::string,std::string> fields; };
struct Fact { std::string key,value,source; EvidenceQuality quality{EvidenceQuality::observed}; std::chrono::system_clock::time_point at{std::chrono::system_clock::now()}; };
struct Alert { std::string id,title,detail; Severity severity{Severity::warning}; unsigned occurrences{1}; bool acknowledged{false}; };
struct Snapshot { std::vector<Fact> facts; std::vector<Event> events; std::vector<Alert> alerts; };
class StabilityService {
 public: explicit StabilityService(std::size_t max_events=4096):max_events_(max_events){}
 void ingest(Event e); void add_fact(Fact f); std::optional<Alert> analyze(const Event&) const; Snapshot snapshot() const;
 std::vector<Event> filter(std::string_view domain, Severity minimum) const; void acknowledge(std::string_view id);
 private: std::size_t max_events_; std::deque<Event> events_; std::map<std::string,Fact> facts_; std::map<std::string,Alert> alerts_;
};
class JournalNormalizer { public: static Event normalize(std::string_view line); };
class HealthClassifier { public: static std::optional<Alert> classify(const Event&); };
}