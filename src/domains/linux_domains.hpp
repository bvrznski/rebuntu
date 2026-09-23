#pragma once
#include <providers/linux/backend.hpp>
#include <control/domain_controller.hpp>
#include <map>
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::domains {
struct Operation {
  backend::Command command;
  std::optional<backend::Command> verify;
  std::optional<backend::Command> rollback;
  bool mutating{true};
  std::string expected;
};
struct Probe { std::string key; backend::Command command; };
class LinuxDomain {
public:
  virtual ~LinuxDomain()=default;
  virtual management::Domain domain() const=0;
  virtual Operation plan(const management::Request&, const std::optional<std::string>& before) const=0;
  virtual std::vector<Probe> probes(const std::string& target) const=0;
};
class LinuxDomainRegistry {
public:
  LinuxDomainRegistry();
  const LinuxDomain& get(management::Domain) const;
private:
  std::map<management::Domain,std::unique_ptr<LinuxDomain>> domains_;
};
}
