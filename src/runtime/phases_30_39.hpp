#pragma once
#include <runtime/phases_20_30.hpp>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
namespace rebuntu::platform::v3039 {
using Fields=rebuntu::platform::Fields; using Decision=rebuntu::platform::Decision;
struct PhaseCapability { int major{},minor{}; std::string file,title,heading; };
class PhaseRegistry { public: PhaseRegistry(); const std::vector<PhaseCapability>& all() const; std::vector<PhaseCapability> domain(int major) const; std::optional<PhaseCapability> find(int major,int minor) const; bool complete() const; private: std::vector<PhaseCapability> phases_; };
struct Object { std::string id,kind,provider,state; Fields attributes; };
struct Change { std::string domain,action,target; Fields desired; bool privileged{false},destructive{false}; };
struct DomainHealth { bool available{false}; std::string provider; std::vector<std::string> issues; Fields metrics; };
class LinuxDomain { public: explicit LinuxDomain(int major); int major()const{return major_;} std::string name()const; std::vector<std::string> providers()const; std::vector<Object> discover()const; DomainHealth health()const; Decision validate(const Change&,bool confirmed=false,bool privileged=false)const; Fields snapshot()const; private:int major_; };
struct ClosureReport { bool ready{false}; std::map<int,bool> domains; std::vector<std::string> issues; std::size_t registered_phases{}; };
class System3039 { public: System3039(); PhaseRegistry phases; LinuxDomain resources,services,storage,network,accelerators,software,configuration,secrets,identity,timeline; ClosureReport audit()const; };
}
