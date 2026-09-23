#pragma once
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>
namespace rebuntu::core::state {
class StateMachine {
  std::string current_; std::map<std::string,std::set<std::string>> allowed_;
public:
  explicit StateMachine(std::string initial): current_(std::move(initial)) {}
  void allow(std::string from,std::string to){allowed_[std::move(from)].insert(std::move(to));}
  const std::string& current() const noexcept { return current_; }
  bool can_transition_to(const std::string& to) const { auto i=allowed_.find(current_); return i!=allowed_.end() && i->second.contains(to); }
  bool transition_to(const std::string& to){ if(!can_transition_to(to)) return false; current_=to; return true; }
};}
