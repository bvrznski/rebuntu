#pragma once
#include <chrono>
#include <string>
#include <vector>
namespace rebuntu::core::evidence {
struct Record { std::string subject, source, authority, value; std::chrono::system_clock::time_point observed_at; };
class Store { std::vector<Record> records_; public: void append(Record r){records_.push_back(std::move(r));} const std::vector<Record>& records() const noexcept{return records_;} std::vector<Record> for_subject(const std::string& s) const {std::vector<Record> out; for(const auto& r:records_) if(r.subject==s) out.push_back(r); return out;} };
}
