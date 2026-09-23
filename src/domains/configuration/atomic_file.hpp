#pragma once
#include <filesystem>
#include <optional>
#include <string>
namespace rebuntu::domains::configuration {
struct WriteResult { bool changed{false}; std::optional<std::filesystem::path> backup; };
class AtomicFile {
public:
 static std::string read(const std::filesystem::path& path);
 static WriteResult replace(const std::filesystem::path& path, const std::string& content, bool backup=true);
};
}
