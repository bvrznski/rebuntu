#pragma once
#include <chrono>
#include <cstdint>
#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::telemetry {
struct Event {
    std::chrono::system_clock::time_point at{};
    std::string subsystem;
    std::string operation;
    std::string target;
    bool success{false};
    std::chrono::microseconds latency{};
    std::map<std::string,std::string> attributes;
};
struct Counter { std::uint64_t attempts{}, successes{}, failures{}; std::chrono::microseconds total_latency{}; };
class Telemetry {
public:
    void record(Event event);
    Counter counter(const std::string& subsystem,const std::string& operation) const;
    std::vector<Event> recent(std::size_t limit=128) const;
    std::vector<Event> for_target(const std::string& target,std::size_t limit=128) const;
private:
    mutable std::mutex mutex_;
    std::vector<Event> events_;
    std::map<std::pair<std::string,std::string>,Counter> counters_;
};
}
