#pragma once
#include <chrono>
#include <map>
#include <string>
#include <vector>
namespace rebuntu::health { struct Sample{std::string metric;double value{};std::chrono::steady_clock::time_point at{std::chrono::steady_clock::now()};}; struct Trend{double latest{},mean{},slope{};bool anomalous{};}; class HealthMonitor{public:void record(Sample);Trend trend(const std::string&)const;std::vector<std::string> degraded()const;private:std::map<std::string,std::vector<Sample>> samples_;}; }
