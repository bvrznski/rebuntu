#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::domains::process {struct Process{int pid{-1},ppid{-1};std::string name,state,cmdline;long nice{0};unsigned long long start_ticks{0};};class Inventory{public:explicit Inventory(std::filesystem::path proc="/proc"):proc_(std::move(proc)){}std::optional<Process>get(int pid)const;std::vector<Process>all()const;private:std::filesystem::path proc_;};}
