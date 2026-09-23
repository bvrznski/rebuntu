#include "component.hpp"

namespace rebuntu::runtime::environment_foundation {
namespace {
std::filesystem::path env_or(const std::map<std::string,std::string>& env, const char* key,
                             const std::filesystem::path& fallback) {
    const auto it = env.find(key);
    return (it != env.end() && !it->second.empty()) ? std::filesystem::path(it->second) : fallback;
}
bool absolute_or_empty(const std::filesystem::path& p) { return p.empty() || p.is_absolute(); }
}

EnvironmentAssessment EnvironmentFoundationComponent::assess_user(
    const std::filesystem::path& home, const std::map<std::string,std::string>& env) const {
    EnvironmentAssessment out;
    out.layout.scope = Scope::kUser;
    if (home.empty() || !home.is_absolute()) {
        out.issues.push_back({"invalid_home", "home must be an absolute path obtained from native identity authority"});
        return out;
    }
    out.layout.config = env_or(env, "XDG_CONFIG_HOME", home / ".config") / "rebuntu";
    out.layout.state = env_or(env, "XDG_STATE_HOME", home / ".local/state") / "rebuntu";
    out.layout.cache = env_or(env, "XDG_CACHE_HOME", home / ".cache") / "rebuntu";
    out.layout.data = env_or(env, "XDG_DATA_HOME", home / ".local/share") / "rebuntu";
    if (const auto it = env.find("XDG_RUNTIME_DIR"); it != env.end() && !it->second.empty())
        out.layout.runtime = std::filesystem::path(it->second) / "rebuntu";

    for (const auto* p : {&out.layout.config, &out.layout.state, &out.layout.cache, &out.layout.data})
        if (!absolute_or_empty(*p)) out.issues.push_back({"relative_xdg_path", p->string()});
    if (out.layout.runtime && !out.layout.runtime->is_absolute())
        out.issues.push_back({"relative_runtime_path", out.layout.runtime->string()});
    return out;
}

EnvironmentAssessment EnvironmentFoundationComponent::assess_system() const {
    EnvironmentAssessment out;
    out.layout.scope = Scope::kSystem;
    out.layout.config = "/etc/rebuntu";
    out.layout.state = "/var/lib/rebuntu";
    out.layout.cache = "/var/cache/rebuntu";
    out.layout.data = "/usr/share/rebuntu";
    out.layout.runtime = "/run/rebuntu";
    return out;
}

} // namespace rebuntu::runtime::environment_foundation
