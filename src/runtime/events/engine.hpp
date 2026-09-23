#pragma once
#include <chrono>
#include <deque>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::events {
struct Event{std::string id,type,source,subject,message;std::chrono::system_clock::time_point at{std::chrono::system_clock::now()};std::map<std::string,std::string>attributes;};struct Assertion{std::string id,subject,predicate,value;double confidence{1.0};};struct Condition{std::string id;std::function<bool(const Assertion&)>matches;};struct Rule{std::string id;Condition condition;std::string alert_title;};struct Violation{std::string rule_id,assertion_id,detail;};
class Engine{public:explicit Engine(size_t capacity=8192):capacity_(capacity){}void add_rule(Rule);std::vector<Violation>ingest(Event);std::vector<Event>recent()const;std::vector<Assertion>assertions()const{return assertions_;}std::vector<Event>correlate(std::string_view subject,std::chrono::seconds window)const;private:size_t capacity_;std::deque<Event>events_;std::vector<Assertion>assertions_;std::vector<Rule>rules_;std::map<std::string,std::chrono::system_clock::time_point>dedupe_;};
}