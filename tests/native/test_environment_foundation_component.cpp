#include <runtime/environment-foundation/component.hpp>
#include <iostream>
int main() {
    rebuntu::runtime::environment_foundation::EnvironmentFoundationComponent c;
    const auto u = c.assess_user("/home/alice", {{"XDG_CONFIG_HOME","/cfg"},{"XDG_RUNTIME_DIR","/run/user/1000"}});
    if (!u.usable() || u.layout.config != "/cfg/rebuntu" || !u.layout.runtime || *u.layout.runtime != "/run/user/1000/rebuntu") return 1;
    const auto bad = c.assess_user("relative", {});
    if (bad.usable()) return 2;
    const auto s = c.assess_system();
    if (!s.usable() || s.layout.state != "/var/lib/rebuntu" || !s.layout.runtime || *s.layout.runtime != "/run/rebuntu") return 3;
    std::cout << "ENVIRONMENT_FOUNDATION_PASS\n";
}
