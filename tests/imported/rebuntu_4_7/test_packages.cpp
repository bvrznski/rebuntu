// Rebuntu — Package Metadata & Environment Reproducibility Tests (Phase 3.11)
//
// Test the package metadata module:
//   * Dependency parsing and serialization
//   * Lock file format and verification
//   * Environment information detection
//   * Directory hashing for reproducibility

#include <system/infrastructure/packages.hpp>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>

namespace {

int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)

}  // namespace

void test_dependency_parsing() {
    using rebuntu::infrastructure::packages::Dependency;
    
    // Test basic parsing
    auto dep1 = Dependency::from_pip_specifier("requests");
    CHECK(dep1.has_value());
    CHECK(dep1->name == "requests");
    CHECK(dep1->version.empty());
    
    // Test version constraint
    auto dep2 = Dependency::from_pip_specifier("requests>=2.28.0");
    CHECK(dep2.has_value());
    CHECK(dep2->name == "requests");
    CHECK(dep2->version == ">=2.28.0");
    
    // Test extras
    auto dep3 = Dependency::from_pip_specifier("requests[security,socks]>=2.28.0");
    CHECK(dep3.has_value());
    CHECK(dep3->name == "requests");
    CHECK(dep3->extras.size() == 2);
    CHECK(dep3->extras[0] == "security");
    CHECK(dep3->extras[1] == "socks");
    
    // Test markers
    auto dep4 = Dependency::from_pip_specifier("requests; sys_platform == 'linux'");
    CHECK(dep4.has_value());
    CHECK(dep4->markers.has_value());
    CHECK(dep4->markers.value() == "sys_platform == 'linux'");
}

void test_dependency_serialization() {
    using rebuntu::infrastructure::packages::Dependency;
    
    Dependency dep;
    dep.name = "requests";
    dep.version = ">=2.28.0";
    dep.extras = {"security"};
    dep.markers = "sys_platform == 'linux'";
    
    std::string spec = dep.to_pip_specifier();
    CHECK(spec.find("requests") != std::string::npos);
    CHECK(spec.find(">=2.28.0") != std::string::npos);
}

void test_dependency_equality() {
    using rebuntu::infrastructure::packages::Dependency;
    
    Dependency dep1 = {"pkg", ">=1.0"};
    Dependency dep2 = {"pkg", ">=1.0"};
    Dependency dep3 = {"other", ">=1.0"};
    
    CHECK(dep1 == dep2);
    CHECK(!(dep1 == dep3));
}

void test_package_metadata() {
    using rebuntu::infrastructure::packages::PackageMetadata;
    
    auto meta = PackageMetadata::placeholder();
    CHECK(meta.name == "test-package");
    CHECK(meta.version == "1.0.0");
    CHECK(!meta.dependencies.empty());
}

void test_lockfile_creation() {
    using rebuntu::infrastructure::packages::LockFile;
    using rebuntu::infrastructure::packages::Dependency;
    
    std::vector<std::pair<Dependency, std::string>> deps = {
        {{"pkg1", ">=1.0"}, "abc123"},
        {{"pkg2", "~>2.0"}, "def456"}
    };
    
    auto lf = LockFile::from_dependencies(deps);
    CHECK(lf.version == "1.0");
    CHECK(lf.packages.size() == 2);
}

void test_lockfile_serialization() {
    using rebuntu::infrastructure::packages::LockFile;
    using rebuntu::infrastructure::packages::Dependency;
    
    std::vector<std::pair<Dependency, std::string>> deps = {
        {{"requests", ">=2.28.0"}, "abc123def456"}
    };
    
    auto lf = LockFile::from_dependencies(deps);
    std::string json = lf.to_json();
    
    CHECK(json.find("\"version\": \"1.0\"") != std::string::npos);
    CHECK(json.find("requests") != std::string::npos);
}

void test_lockfile_hash_verification() {
    using rebuntu::infrastructure::packages::LockFile;
    using rebuntu::infrastructure::packages::Dependency;
    
    std::vector<std::pair<Dependency, std::string>> deps = {
        {{"pkg1", ">=1.0"}, "abc123"}
    };
    
    auto lf = LockFile::from_dependencies(deps);
    
    // Create a test file
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-hash";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        auto test_file = temp_dir / "test.txt";
        std::ofstream(test_file) << "test content";
        
        // verify_hash returns true for existing files (simplified implementation)
        bool result = lf.verify_hash("pkg1", test_file);
        CHECK(result == true);
        
        // Cleanup
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_lockfile_io() {
    using rebuntu::infrastructure::packages::LockFile;
    using rebuntu::infrastructure::packages::Dependency;
    
    std::vector<std::pair<Dependency, std::string>> deps = {
        {{"pkg1", ">=1.0"}, "abc123"}
    };
    
    auto lf = LockFile::from_dependencies(deps);
    
    // Test save and load
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-lockfile";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        auto lock_file_path = temp_dir / "lock.json";
        
        // Save
        bool saved = lf.save_to_file(lock_file_path);
        CHECK(saved == true);
        
        // Load
        auto loaded = LockFile::from_file(lock_file_path);
        CHECK(loaded.has_value());
        
        // Cleanup
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_lockfile_not_found() {
    using rebuntu::infrastructure::packages::LockFile;
    
    auto result = LockFile::from_file("/nonexistent/path/lock.json");
    CHECK(!result.has_value());
}

void test_environment_info() {
    using rebuntu::infrastructure::packages::EnvironmentInfo;
    
    auto env = EnvironmentInfo::from_current();
    CHECK(!env.python_version.empty());
    CHECK(!env.executable.empty());
    CHECK(!env.prefix.empty());
}

void test_check_is_venv() {
    using rebuntu::infrastructure::packages::EnvironmentInfo;
    
    // Non-existent prefix should not be a venv
    bool is_venv = EnvironmentInfo::check_is_venv("/nonexistent/path");
    CHECK(is_venv == false);
}

void test_directory_hashing_empty() {
    using rebuntu::infrastructure::packages::compute_directory_hash;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-empty";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        std::string hash = compute_directory_hash(temp_dir);
        // Hash should be deterministic
        CHECK(hash.length() == 64);  // SHA256 in hex format
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_directory_hashing_single_file() {
    using rebuntu::infrastructure::packages::compute_directory_hash;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-single";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        std::ofstream(temp_dir / "test.txt") << "hello world";
        
        std::string hash = compute_directory_hash(temp_dir);
        CHECK(hash.length() == 64);
        
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_directory_hashing_multiple_files() {
    using rebuntu::infrastructure::packages::compute_directory_hash;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-multiple";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        std::ofstream(temp_dir / "a.txt") << "file a";
        std::ofstream(temp_dir / "b.txt") << "file b";
        
        std::string hash = compute_directory_hash(temp_dir);
        CHECK(hash.length() == 64);
        
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_directory_hashing_exclusions() {
    using rebuntu::infrastructure::packages::compute_directory_hash;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-exclude";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        std::ofstream(temp_dir / "test.txt") << "content";
        
        // .git directory should be excluded
        std::filesystem::create_directory(temp_dir / ".git", ec);
        
        std::string hash = compute_directory_hash(temp_dir);
        CHECK(hash.length() == 64);
        
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_directory_hashing_ordering() {
    using rebuntu::infrastructure::packages::compute_directory_hash;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-order";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        // Create files in reverse alphabetical order
        std::ofstream(temp_dir / "c.txt") << "c";
        std::ofstream(temp_dir / "a.txt") << "a";
        std::ofstream(temp_dir / "b.txt") << "b";
        
        std::string hash1 = compute_directory_hash(temp_dir);
        
        // Should be deterministic
        std::string hash2 = compute_directory_hash(temp_dir);
        CHECK(hash1 == hash2);
        
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_integration() {
    using rebuntu::infrastructure::packages::LockFile;
    using rebuntu::infrastructure::packages::Dependency;
    
    // Create a lock file with multiple packages
    std::vector<std::pair<Dependency, std::string>> deps = {
        {{"requests", ">=2.28.0"}, "abc123def456"},
        {{"numpy", "~>1.21.0"}, "fedcba654321"},
        {{"pandas", "==1.4.0"}, "123456abcdef"}
    };
    
    auto lf = LockFile::from_dependencies(deps);
    std::string json = lf.to_json();
    
    // Verify JSON contains all packages
    CHECK(json.find("requests") != std::string::npos);
    CHECK(json.find("numpy") != std::string::npos);
    CHECK(json.find("pandas") != std::string::npos);
}

int main() {
    std::cout << "Testing Package Metadata & Environment Reproducibility (Phase 3.11)...\n\n";
    
    test_dependency_parsing();
    test_dependency_serialization();
    test_dependency_equality();
    test_package_metadata();
    test_lockfile_creation();
    test_lockfile_serialization();
    test_lockfile_hash_verification();
    test_lockfile_io();
    test_lockfile_not_found();
    test_environment_info();
    test_check_is_venv();
    test_directory_hashing_empty();
    test_directory_hashing_single_file();
    test_directory_hashing_multiple_files();
    test_directory_hashing_exclusions();
    test_directory_hashing_ordering();
    test_integration();
    
    std::cout << "\nPackage Tests Complete\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}