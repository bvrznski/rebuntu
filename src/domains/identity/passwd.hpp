#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
#include <sys/types.h>
namespace rebuntu::domains::identity {
struct User {std::string name;uid_t uid{};gid_t gid{};std::string gecos,home,shell;};
class PasswdDatabase {public:explicit PasswdDatabase(std::filesystem::path p="/etc/passwd"):path_(std::move(p)){}std::vector<User>all()const;std::optional<User>find(const std::string&)const;std::optional<User>find(uid_t)const;private:std::filesystem::path path_;};
}
