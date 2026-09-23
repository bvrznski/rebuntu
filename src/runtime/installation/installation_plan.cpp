#include "installation_plan.hpp"
#include <stdexcept>
namespace rebuntu::runtime::installation {
Plan Planner::build(const Intent& intent, const preflight::Report& host) const {
    if (intent.install_root.empty() || intent.install_root.front() != '/') throw std::invalid_argument("install_root must be absolute");
    Plan p; p.target_state="rebuntu installed at "+intent.install_root; p.dry_run=intent.dry_run; p.executable=host.ready();
    if (!host.ready()) p.warnings.push_back("host preflight has blockers; plan is reviewable but not executable");
    p.steps.push_back({"prepare-staging",intent.install_root,"prepare secure staging area",{},false,true,"staging path exists with restrictive ownership",true});
    for (const auto& d : intent.dependencies) {
        if (!d.required && d.classification != DependencyClass::optional_feature) continue;
        p.steps.push_back({"dependency-"+d.name,d.name,"ensure dependency",{"prepare-staging"},true,true,"dependency is available at required version",false});
    }
    p.steps.push_back({"install-core",intent.install_root,"install verified Rebuntu artifacts",{"prepare-staging"},true,true,"installed artifacts match manifest",true});
    p.steps.push_back({"verify",intent.install_root,"verify target state",{"install-core"},false,false,"installation target satisfies manifest and runtime preconditions",false});
    if (intent.dry_run) p.warnings.push_back("dry-run describes intended operations from current observations; it does not guarantee later execution success");
    return p;
}
}
