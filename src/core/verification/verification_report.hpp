#pragma once
#include <string>
#include <vector>
namespace rebuntu::core::verification {
struct Finding { std::string invariant; bool satisfied; std::string evidence; };
class Report { std::vector<Finding> findings_; public: void add(Finding f){findings_.push_back(std::move(f));} bool converged() const {for(const auto& f:findings_) if(!f.satisfied) return false; return true;} const std::vector<Finding>& findings() const noexcept{return findings_;} };
}
