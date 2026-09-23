#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::domains::package {
struct Package {std::string name,version,architecture,status; bool installed()const;};
class DpkgStatus {public: explicit DpkgStatus(std::filesystem::path path="/var/lib/dpkg/status"):path_(std::move(path)){} std::vector<Package> all()const; std::optional<Package> find(const std::string&)const;private:std::filesystem::path path_;};
}
