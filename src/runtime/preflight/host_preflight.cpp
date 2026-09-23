#include "host_preflight.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <sys/utsname.h>
#include <unistd.h>

namespace rebuntu::runtime::preflight {
namespace {
std::string trim_quotes(std::string v) {
    if (v.size() >= 2 && v.front() == '"' && v.back() == '"') return v.substr(1, v.size()-2);
    return v;
}
void put(std::map<std::string, Fact>& f, std::string k, std::string v, std::string source) {
    f[k] = Fact{k, std::move(v), std::move(source), !v.empty()};
}
bool contains(const std::vector<std::string>& xs, const std::string& v) {
    return std::find(xs.begin(), xs.end(), v) != xs.end();
}
}

bool Report::ready() const {
    return std::none_of(findings.begin(), findings.end(), [](const Finding& f){return f.severity == Severity::blocker;});
}

std::string Report::human_summary() const {
    std::ostringstream out;
    out << "host preflight: " << (ready() ? "READY" : "BLOCKED") << "\n";
    for (const auto& [key, fact] : facts) out << key << '=' << (fact.known ? fact.value : "UNKNOWN") << " [" << fact.source << "]\n";
    for (const auto& f : findings) out << (f.severity == Severity::blocker ? "BLOCKER" : f.severity == Severity::warning ? "WARNING" : "INFO") << ": " << f.requirement << ": " << f.message << "\n";
    return out.str();
}

Report HostPreflight::inspect(const Policy& policy) const {
    std::map<std::string, Fact> facts;
    std::ifstream os("/etc/os-release");
    std::string line;
    while (std::getline(os, line)) {
        const auto p = line.find('='); if (p == std::string::npos) continue;
        const auto k = line.substr(0,p); const auto v = trim_quotes(line.substr(p+1));
        if (k == "ID") put(facts, "distribution", v, "/etc/os-release:ID");
        if (k == "VERSION_ID") put(facts, "distribution_version", v, "/etc/os-release:VERSION_ID");
    }
    struct utsname u{};
    if (::uname(&u) == 0) { put(facts,"kernel",u.release,"uname(2)"); put(facts,"architecture",u.machine,"uname(2)"); }
    put(facts,"effective_uid",std::to_string(::geteuid()),"geteuid(2)");
    if (const char* h = ::getenv("HOME")) put(facts,"home",h,"environment:HOME");
    if (const char* s = ::getenv("SHELL")) put(facts,"shell",s,"environment:SHELL");
    put(facts,"systemd", std::filesystem::exists("/run/systemd/system") ? "available" : "unavailable", "/run/systemd/system");
    std::string pm = std::filesystem::exists("/usr/bin/apt-get") ? "apt" : std::filesystem::exists("/usr/bin/dnf") ? "dnf" : std::filesystem::exists("/usr/bin/pacman") ? "pacman" : "";
    put(facts,"package_manager",pm,"filesystem executable discovery");
    std::error_code ec; const auto sp = std::filesystem::space("/",ec);
    if (!ec) put(facts,"root_free_bytes",std::to_string(sp.available),"statvfs via std::filesystem::space");
    return evaluate(std::move(facts), policy);
}

Report HostPreflight::evaluate(std::map<std::string, Fact> facts, const Policy& policy) {
    Report r; r.facts = std::move(facts);
    auto value = [&](const std::string& k)->std::string { auto i=r.facts.find(k); return i==r.facts.end()||!i->second.known ? "" : i->second.value; };
    const auto arch=value("architecture");
    if (arch.empty()) r.findings.push_back({Severity::warning,"architecture","architecture is unknown"});
    else if (!contains(policy.supported_architectures,arch)) r.findings.push_back({Severity::blocker,"architecture","unsupported architecture: "+arch});
    const auto distro=value("distribution");
    if (distro.empty()) { r.support=SupportLevel::unknown; r.findings.push_back({Severity::warning,"distribution","distribution is unknown; not assumed unsupported"}); }
    else if (contains(policy.tested_distributions,distro)) r.support=SupportLevel::tested;
    else { r.support=SupportLevel::unknown; r.findings.push_back({Severity::warning,"distribution","distribution is not in the tested set"}); }
    if (policy.require_systemd && value("systemd") != "available") r.findings.push_back({Severity::blocker,"systemd","systemd system manager is required by this installation profile"});
    if (value("package_manager").empty()) r.findings.push_back({Severity::blocker,"package_manager","no supported package manager discovered"});
    const auto free=value("root_free_bytes");
    if (!free.empty()) { try { if (std::stoull(free) < policy.minimum_free_bytes) r.findings.push_back({Severity::blocker,"free_space","insufficient free space"}); } catch (...) { r.findings.push_back({Severity::warning,"free_space","free-space observation is invalid"}); } }
    else r.findings.push_back({Severity::warning,"free_space","free space is unknown"});
    return r;
}
}
