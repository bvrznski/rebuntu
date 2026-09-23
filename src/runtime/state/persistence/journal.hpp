#pragma once
#include <filesystem>
#include <mutex>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::persistence {
struct JournalEntry{std::string transaction_id,domain,target,action,before_value,after_value,status;};
class Journal{public:explicit Journal(std::filesystem::path path);void append(const JournalEntry&);std::vector<JournalEntry> load()const;std::optional<JournalEntry> latest(const std::string& target)const;private:std::filesystem::path path_;mutable std::mutex mutex_;};
}
