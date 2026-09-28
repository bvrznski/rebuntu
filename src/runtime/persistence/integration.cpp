#include "integration.hpp"

#include <fstream>
#include <filesystem>

namespace rebuntu::runtime::persistence {

FilesystemPersistence::FilesystemPersistence(const std::string& storage_path)
    : storage_path_(storage_path) {
    // Ensure storage directory exists
    std::filesystem::create_directories(storage_path_);
}

FilesystemPersistence::~FilesystemPersistence() = default;

FilesystemPersistence::FilesystemPersistence(FilesystemPersistence&&) noexcept = default;
FilesystemPersistence& FilesystemPersistence::operator=(FilesystemPersistence&&) noexcept = default;

bool FilesystemPersistence::save(const ExecutionRecord& record) {
    // Generate filename from execution_id (base64-safe: replace / with _)
    std::string safe_exec_id = record.execution_id;
    for (char& c : safe_exec_id) {
        if (c == '/') c = '_';
    }
    
    std::string filepath = storage_path_ + "/" + safe_exec_id + ".exec";
    
    std::ofstream out(filepath);
    if (!out.is_open()) {
        return false;
    }
    
    // Write record in a simple key=value format
    long start_ts = record.started_at_ms;
    long end_ts = record.finished_at_ms;
    
    out << "request_id=" << record.request_id << "\n";
    out << "execution_id=" << record.execution_id << "\n";
    out << "parent_execution_id=" << record.parent_execution_id << "\n";
    out << "started_at=" << start_ts << "\n";
    out << "finished_at=" << end_ts << "\n";
    out << "outcome=" << record.outcome << "\n";
    out << "verification_successful=" << (record.verification_successful ? "1" : "0") << "\n";
    out << "attempt_number=" << record.attempt_number << "\n";
    out << "was_cancelled=" << (record.was_cancelled ? "1" : "0") << "\n";
    out << "timed_out=" << (record.timed_out ? "1" : "0") << "\n";
    
    if (!record.result_summary.empty()) {
        out << "result_summary=" << record.result_summary << "\n";
    }
    
    for (const auto& ref : record.evidence_refs) {
        out << "evidence_ref=" << ref << "\n";
    }
    
    return true;
}

std::optional<ExecutionRecord> FilesystemPersistence::load(const std::string& exec_id) {
    // Generate filename from execution_id
    std::string safe_exec_id = exec_id;
    for (char& c : safe_exec_id) {
        if (c == '/') c = '_';
    }
    
    std::string filepath = storage_path_ + "/" + safe_exec_id + ".exec";
    
    std::ifstream in(filepath);
    if (!in.is_open()) {
        return std::nullopt;
    }
    
    ExecutionRecord record{};
    std::string line;
    
    while (std::getline(in, line)) {
        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) continue;
        
        std::string key = line.substr(0, eq_pos);
        std::string value = line.substr(eq_pos + 1);
        
        if (key == "request_id") record.request_id = value;
        else if (key == "execution_id") record.execution_id = value;
        else if (key == "parent_execution_id") record.parent_execution_id = value;
        else if (key == "started_at") record.started_at_ms = std::stoll(value);
        else if (key == "finished_at") record.finished_at_ms = std::stoll(value);
        else if (key == "outcome") record.outcome = std::stoi(value);
        else if (key == "verification_successful") record.verification_successful = (value == "1");
        else if (key == "attempt_number") record.attempt_number = std::stoi(value);
        else if (key == "was_cancelled") record.was_cancelled = (value == "1");
        else if (key == "timed_out") record.timed_out = (value == "1");
        else if (key == "result_summary") record.result_summary = value;
        else if (key == "evidence_ref") record.evidence_refs.push_back(value);
    }
    
    return record;
}

std::vector<ExecutionRecord> FilesystemPersistence::list_by_request(const std::string& req_id) {
    std::vector<ExecutionRecord> results;
    
    for (const auto& entry : std::filesystem::directory_iterator(storage_path_)) {
        if (!entry.is_regular_file()) continue;
        
        std::string filename = entry.path().filename().string();
        if (filename.substr(filename.find_last_of('.') + 1) != "exec") continue;
        
        // Try to load and check request_id
        auto record_opt = load(entry.path().stem().string());
        if (record_opt && record_opt->request_id == req_id) {
            results.push_back(std::move(*record_opt));
        }
    }
    
    return results;
}

std::vector<ExecutionRecord> FilesystemPersistence::list_recent(int limit) {
    std::vector<std::pair<long, ExecutionRecord>> records;
    
    for (const auto& entry : std::filesystem::directory_iterator(storage_path_)) {
        if (!entry.is_regular_file()) continue;
        
        std::string filename = entry.path().filename().string();
        if (filename.substr(filename.find_last_of('.') + 1) != "exec") continue;
        
        auto record_opt = load(entry.path().stem().string());
        if (record_opt) {
            records.emplace_back(record_opt->started_at_ms, std::move(*record_opt));
        }
    }
    
    // Sort by started_at descending (most recent first)
    std::sort(records.begin(), records.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });
    
    // Return up to limit
    std::vector<ExecutionRecord> result;
    int count = 0;
    for (const auto& [ts, record] : records) {
        if (count >= limit) break;
        result.push_back(record);
        count++;
    }
    
    return result;
}

bool FilesystemPersistence::remove(const std::string& exec_id) {
    // Generate filename from execution_id
    std::string safe_exec_id = exec_id;
    for (char& c : safe_exec_id) {
        if (c == '/') c = '_';
    }
    
    std::string filepath = storage_path_ + "/" + safe_exec_id + ".exec";
    return std::filesystem::remove(filepath);
}

void FilesystemPersistence::clear() {
    for (const auto& entry : std::filesystem::directory_iterator(storage_path_)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.substr(filename.find_last_of('.') + 1) == "exec") {
                std::filesystem::remove(entry.path());
            }
        }
    }
}

}  // namespace rebuntu::runtime::persistence