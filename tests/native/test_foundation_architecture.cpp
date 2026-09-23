#include <runtime/foundation/component.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

int main() {
    namespace fs = std::filesystem;
    using rebuntu::runtime::foundation::FoundationComponent;
    const auto root = fs::temp_directory_path() / "rebuntu-foundation-test";
    fs::remove_all(root);
    FoundationComponent component;
    for (const auto& req : component.canonical_requirements()) {
        const auto p = root / req.relative_path;
        if (req.directory) fs::create_directories(p);
        else { fs::create_directories(p.parent_path()); std::ofstream(p) << "contract\n"; }
    }
    auto audit = component.audit(root);
    if (!audit.satisfied() || audit.missing_count() != 0) return 1;
    fs::remove_all(root / "src/planning");
    audit = component.audit(root);
    if (audit.satisfied() || audit.missing_count() != 1) return 2;
    fs::remove_all(root);
    std::cout << "FOUNDATION_ARCHITECTURE_PASS\n";
}
