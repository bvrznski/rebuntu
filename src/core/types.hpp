#pragma once
#include <chrono>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
namespace rebuntu::core {
using Attributes = std::map<std::string,std::string>;
struct Evidence { std::string source; std::string authority; std::string value; std::chrono::system_clock::time_point observed_at{}; };
struct Entity { std::string id; std::string kind; Attributes attributes; std::vector<Evidence> evidence; };
struct DesiredState { std::string entity_id; Attributes attributes; std::string reason; };
struct NativeOperation { std::string provider; std::string verb; std::string target; Attributes arguments; bool mutating{false}; };
struct Verification { bool converged{false}; std::vector<std::string> mismatches; std::vector<Evidence> evidence; };
struct Plan { std::string id; std::vector<NativeOperation> operations; std::vector<std::string> preconditions; std::vector<std::string> postconditions; };
}
