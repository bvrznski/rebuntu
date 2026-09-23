// rebuntu::testing::fixtures — Test Fixture Utilities (Phase 3.12)
//
// Comprehensive fixture patterns for testing Rebuntu components:
//   * Safe temporary environments with mock providers
//   * IPC fixtures and execution harnesses
//   * XDG-style directory tree management

#pragma once

#include <system/testing/contracts.hpp>
#include <system/environment/temp_files.hpp>

#include <filesystem>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <memory>

namespace rebuntu::testing {

// ============================================================================
// FixtureState - RAII state for test fixtures
// ============================================================================

class FixtureState {
public:
    explicit FixtureState(TestEnvironmentConfig config);
    ~FixtureState();
    
    // Non-copyable, movable
    FixtureState(const FixtureState&) = delete;
    FixtureState& operator=(const FixtureState&) = delete;
    FixtureState(FixtureState&&) noexcept;
    FixtureState& operator=(FixtureState&&) noexcept;
    
    const std::filesystem::path& temp_root() const { return temp_dir_.path(); }
    const TestEnvironmentConfig& config() const { return config_; }
    
private:
    TestEnvironmentConfig config_;
    environment::temp_files::SecureTempDir temp_dir_;
};

// ============================================================================
// XdgTree - Managed XDG-style directory tree
// ============================================================================

class XdgTree {
public:
    explicit XdgTree(const std::filesystem::path& root);
    ~XdgTree();
    
    // Non-copyable, movable
    XdgTree(const XdgTree&) = delete;
    XdgTree& operator=(const XdgTree&) = delete;
    XdgTree(XdgTree&&) noexcept;
    XdgTree& operator=(XdgTree&&) noexcept;
    
    const std::filesystem::path& root() const { return root_; }
    
    // XDG directories
    const std::filesystem::path& cache_home() const { return cache_home_; }
    const std::filesystem::path& config_home() const { return config_home_; }
    const std::filesystem::path& data_home() const { return data_home_; }
    const std::filesystem::path& runtime_dir() const { return runtime_dir_; }
    
    // Create directory and return path
    std::filesystem::path create(const std::string& name);
    
private:
    std::filesystem::path root_;
    std::filesystem::path cache_home_;
    std::filesystem::path config_home_;
    std::filesystem::path data_home_;
    std::filesystem::path runtime_dir_;
};

// ============================================================================
// TempXdgTree - Context manager for XDG path mapping in tests
// ============================================================================

class TempXdgTree {
public:
    explicit TempXdgTree(TestEnvironmentConfig config);
    ~TempXdgTree();
    
    // Non-copyable, movable
    TempXdgTree(const TempXdgTree&) = delete;
    TempXdgTree& operator=(const TempXdgTree&) = delete;
    TempXdgTree(TempXdgTree&&) noexcept;
    TempXdgTree& operator=(TempXdgTree&&) noexcept;
    
    // Get XDG-style path mapping
    std::map<std::string, std::filesystem::path> paths() const;
    
    // Create a file in the temp directory
    environment::temp_files::TempFileResult create_file(
        const std::string& name,
        mode_t permissions = 0600);
    
    // Create a directory in the temp directory
    environment::temp_files::TempFileResult create_dir(
        const std::string& name,
        mode_t permissions = 0700);
    
private:
    TestEnvironmentConfig config_;
    XdgTree xdg_tree_;
};

// ============================================================================
// FakeUnixSocket - Temporary Unix socket fixture
// ============================================================================

class FakeUnixSocket {
public:
    explicit FakeUnixSocket(const std::filesystem::path& path = {});
    ~FakeUnixSocket();
    
    // Non-copyable, non-movable for socket safety
    FakeUnixSocket(const FakeUnixSocket&) = delete;
    FakeUnixSocket& operator=(const FakeUnixSocket&) = delete;
    FakeUnixSocket(FakeUnixSocket&&) noexcept = delete;
    FakeUnixSocket& operator=(FakeUnixSocket&&) noexcept = delete;
    
    const std::filesystem::path& path() const { return path_; }
    bool is_valid() const { return fd_ >= 0; }
    
private:
    std::filesystem::path path_;
    int fd_{-1};
};

// ============================================================================
// FakeProviderFixture - Test provider creation and management
// ============================================================================

class FakeProviderFixture {
public:
    explicit FakeProviderFixture(TestEnvironmentConfig config);
    ~FakeProviderFixture();
    
    // Non-copyable, movable
    FakeProviderFixture(const FakeProviderFixture&) = delete;
    FakeProviderFixture& operator=(const FakeProviderFixture&) = delete;
    FakeProviderFixture(FakeProviderFixture&&) noexcept;
    FakeProviderFixture& operator=(FakeProviderFixture&&) noexcept;
    
    // Create a provider that exits with specified code
    std::filesystem::path create_exit_provider(int exit_code, const std::string& name = "exit");
    
    // Create a provider that writes output to stdout
    std::filesystem::path create_output_provider(
        const std::string& output,
        int exit_code = 0,
        const std::string& name = "output");
    
    // Create a provider that sleeps for specified duration
    std::filesystem::path create_sleep_provider(double seconds, const std::string& name = "sleep");
    
    // Get temp root directory
    const std::filesystem::path& temp_root() const { return temp_dir_.path(); }
    
private:
    TestEnvironmentConfig config_;
    environment::temp_files::SecureTempDir temp_dir_;
};

// ============================================================================
// ProviderExecutionFixture - Provider execution with timeouts and limits
// ============================================================================

class ProviderExecutionFixture {
public:
    explicit ProviderExecutionFixture(TestEnvironmentConfig config);
    ~ProviderExecutionFixture();
    
    // Non-copyable, movable
    ProviderExecutionFixture(const ProviderExecutionFixture&) = delete;
    ProviderExecutionFixture& operator=(const ProviderExecutionFixture&) = delete;
    ProviderExecutionFixture(ProviderExecutionFixture&&) noexcept;
    ProviderExecutionFixture& operator=(ProviderExecutionFixture&&) noexcept;
    
    // Run a command with timeout and output limits
    ProviderExecutorResult run(
        const std::vector<std::string>& argv,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt,
        size_t max_output_size = 65536);
    
    // Get temp root directory
    const std::filesystem::path& temp_root() const { return temp_dir_.path(); }
    
private:
    TestEnvironmentConfig config_;
    environment::temp_files::SecureTempDir temp_dir_;
};

// ============================================================================
// IPCFixture - IPC communication fixtures
// ============================================================================

class IPCFixture {
public:
    explicit IPCFixture(TestEnvironmentConfig config);
    ~IPCFixture();
    
    // Non-copyable, movable
    IPCFixture(const IPCFixture&) = delete;
    IPCFixture& operator=(const IPCFixture&) = delete;
    IPCFixture(IPCFixture&&) noexcept;
    IPCFixture& operator=(IPCFixture&&) noexcept;
    
    // Create a Unix socket for IPC testing
    std::filesystem::path create_unix_socket();
    
    // Get temp root directory
    const std::filesystem::path& temp_root() const { return temp_dir_.path(); }
    
private:
    TestEnvironmentConfig config_;
    environment::temp_files::SecureTempDir temp_dir_;
};

}  // namespace rebuntu::testing

// ============================================================================
// Inline implementations
// ============================================================================

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <thread>
#include <chrono>

namespace rebuntu::testing {

inline FixtureState::FixtureState(TestEnvironmentConfig config)
    : config_(std::move(config))
    , temp_dir_([this]() -> std::filesystem::path {
        static int counter = 0;
        auto dir = config_.temp_root / "fixture-" + std::to_string(counter++);
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        return dir;
    }()) {
}

inline FixtureState::~FixtureState() {
    // temp_dir_ destructor handles cleanup
}

inline FixtureState::FixtureState(FixtureState&&) noexcept = default;
inline FixtureState& FixtureState::operator=(FixtureState&&) noexcept = default;

inline XdgTree::XdgTree(const std::filesystem::path& root)
    : root_(root)
    , cache_home_(root / "cache")
    , config_home_(root / "config")
    , data_home_(root / "share")
    , runtime_dir_(root / "runtime") {
    
    std::error_code ec;
    std::filesystem::create_directories(cache_home_, ec);
    std::filesystem::create_directories(config_home_, ec);
    std::filesystem::create_directories(data_home_, ec);
    std::filesystem::create_directories(runtime_dir_, ec);
}

inline XdgTree::~XdgTree() {
    // Note: We don't delete the root directory as it may be a temp dir managed elsewhere
}

inline XdgTree::XdgTree(XdgTree&&) noexcept = default;
inline XdgTree& XdgTree::operator=(XdgTree&&) noexcept = default;

inline std::filesystem::path XdgTree::create(const std::string& name) {
    auto path = root_ / name;
    std::error_code ec;
    std::filesystem::create_directories(path, ec);
    return path;
}

inline TempXdgTree::TempXdgTree(TestEnvironmentConfig config)
    : config_(std::move(config))
    , xdg_tree_((config_.temp_root / "xdg-" + std::to_string(
        []() { static int counter = 0; return counter++; }()))) {
}

inline TempXdgTree::~TempXdgTree() {
    // xdg_tree_ destructor handles cleanup
}

inline TempXdgTree::TempXdgTree(TempXdgTree&&) noexcept = default;
inline TempXdgTree& TempXdgTree::operator=(TempXdgTree&&) noexcept = default;

inline std::map<std::string, std::filesystem::path> TempXdgTree::paths() const {
    return {
        {"XDG_CACHE_HOME", xdg_tree_.cache_home()},
        {"XDG_CONFIG_HOME", xdg_tree_.config_home()},
        {"XDG_DATA_HOME", xdg_tree_.data_home()},
        {"XDG_RUNTIME_DIR", xdg_tree_.runtime_dir()}
    };
}

inline environment::temp_files::TempFileResult TempXdgTree::create_file(
    const std::string& name,
    mode_t permissions) {
    auto path = xdg_tree_.root() / name;
    std::error_code ec;
    
    // Create parent directory if needed
    auto parent = path.parent_path();
    if (!parent.empty()) {
        std::filesystem::create_directories(parent, ec);
    }
    
    int fd = open(path.c_str(), O_CREAT | O_EXCL | O_RDWR, permissions);
    if (fd < 0) {
        return {environment::temp_files::TempFileStatus::kSystemError, path, -1, 
                std::string{"Failed to create file: "} + strerror(errno)};
    }
    
    return {environment::temp_files::TempFileStatus::kSuccess, path, fd, std::nullopt};
}

inline environment::temp_files::TempFileResult TempXdgTree::create_dir(
    const std::string& name,
    mode_t permissions) {
    auto path = xdg_tree_.root() / name;
    std::error_code ec;
    
    if (std::filesystem::exists(path, ec)) {
        return {environment::temp_files::TempFileStatus::kAlreadyExists, path, -1,
                std::string{"Directory already exists"}};
    }
    
    if (!std::filesystem::create_directory(path, ec)) {
        return {environment::temp_files::TempFileStatus::kSystemError, path, -1,
                std::string{"Failed to create directory: "} + strerror(errno)};
    }
    
    chmod(path.c_str(), permissions);
    
    // Return result with empty fd (directories don't have file descriptors)
    environment::temp_files::TempFileResult result;
    result.status = environment::temp_files::TempFileStatus::kSuccess;
    result.path = path;
    return result;
}

inline FakeUnixSocket::FakeUnixSocket(const std::filesystem::path& path) 
    : path_(path.empty() ? (std::filesystem::temp_directory_path() / 
        ("socket-" + std::to_string(std::hash<std::string>{}(std::to_string(time(nullptr)))))) : path) {
    
    fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_ < 0) return;
    
    // Remove existing socket if present
    unlink(path_.c_str());
    
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path_.c_str(), sizeof(addr.sun_path) - 1);
    
    if (bind(fd_, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        close(fd_);
        fd_ = -1;
        return;
    }
    
    // Listen for connections
    listen(fd_, 1);
}

inline FakeUnixSocket::~FakeUnixSocket() {
    if (fd_ >= 0) {
        close(fd_);
    }
    unlink(path_.c_str());
}

inline FakeProviderFixture::FakeProviderFixture(TestEnvironmentConfig config)
    : config_(std::move(config))
    , temp_dir_([this]() -> std::filesystem::path {
        static int counter = 0;
        auto dir = config_.temp_root / "providers-" + std::to_string(counter++);
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        return dir;
    }()) {
}

inline FakeProviderFixture::~FakeProviderFixture() {
    // temp_dir_ handles cleanup
}

inline FakeProviderFixture::FakeProviderFixture(FakeProviderFixture&&) noexcept = default;
inline FakeProviderFixture& FakeProviderFixture::operator=(FakeProviderFixture&&) noexcept = default;

inline std::filesystem::path FakeProviderFixture::create_exit_provider(
    int exit_code,
    const std::string& name) {
    
    auto source_path = temp_dir_.path() / (name + ".cpp");
    auto binary_path = temp_dir_.path() / name;
    
    std::ofstream source(source_path);
    source << "#include <cstdlib>\n"
           << "int main() { return " << exit_code << "; }\n";
    source.close();
    
    std::string compile_cmd = 
        "g++ -o " + binary_path.string() + " " + source_path.string();
    int result = std::system(compile_cmd.c_str());
    
    if (result != 0) {
        throw std::runtime_error("Failed to create fake provider executable");
    }
    
    chmod(binary_path.c_str(), 0755);
    
    return binary_path;
}

inline std::filesystem::path FakeProviderFixture::create_output_provider(
    const std::string& output,
    int exit_code,
    const std::string& name) {
    
    auto source_path = temp_dir_.path() / (name + ".cpp");
    auto binary_path = temp_dir_.path() / name;
    
    // Escape the output string for C++
    std::string escaped_output;
    for (char c : output) {
        switch (c) {
            case '\n': escaped_output += "\\n"; break;
            case '"':  escaped_output += "\\\""; break;
            case '\\': escaped_output += "\\\\"; break;
            default:   escaped_output += c;
        }
    }
    
    std::ofstream source(source_path);
    source << "#include <iostream>\n"
           << "int main() { \n"
           << "  std::cout << \"" << escaped_output << "\";\n"
           << "  return " << exit_code << "; \n"
           << "}\n";
    source.close();
    
    std::string compile_cmd = 
        "g++ -o " + binary_path.string() + " " + source_path.string();
    int result = std::system(compile_cmd.c_str());
    
    if (result != 0) {
        throw std::runtime_error("Failed to create fake provider executable");
    }
    
    chmod(binary_path.c_str(), 0755);
    
    return binary_path;
}

inline std::filesystem::path FakeProviderFixture::create_sleep_provider(
    double seconds,
    const std::string& name) {
    
    auto source_path = temp_dir_.path() / (name + ".cpp");
    auto binary_path = temp_dir_.path() / name;
    
    std::ofstream source(source_path);
    source << "#include <thread>\n"
           << "#include <chrono>\n"
           << "int main() { \n"
           << "  std::this_thread::sleep_for(std::chrono::duration<double>(" 
           << seconds << "));\n"
           << "  return 0; \n"
           << "}\n";
    source.close();
    
    std::string compile_cmd = 
        "g++ -std=c++17 -o " + binary_path.string() + " " + source_path.string();
    int result = std::system(compile_cmd.c_str());
    
    if (result != 0) {
        throw std::runtime_error("Failed to create fake provider executable");
    }
    
    chmod(binary_path.c_str(), 0755);
    
    return binary_path;
}

inline ProviderExecutionFixture::ProviderExecutionFixture(TestEnvironmentConfig config)
    : config_(std::move(config))
    , temp_dir_([this]() -> std::filesystem::path {
        static int counter = 0;
        auto dir = config_.temp_root / "exec-" + std::to_string(counter++);
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        return dir;
    }()) {
}

inline ProviderExecutionFixture::~ProviderExecutionFixture() {
    // temp_dir_ handles cleanup
}

inline ProviderExecutionFixture::ProviderExecutionFixture(ProviderExecutionFixture&&) noexcept = default;
inline ProviderExecutionFixture& ProviderExecutionFixture::operator=(ProviderExecutionFixture&&) noexcept = default;

inline ProviderExecutorResult ProviderExecutionFixture::run(
    const std::vector<std::string>& argv,
    std::optional<std::chrono::milliseconds> timeout,
    size_t max_output_size) {
    
    ProviderExecutorResult result;
    auto start_time = std::chrono::steady_clock::now();
    
    // Use popen for output capture
    std::string cmd;
    for (const auto& arg : argv) {
        if (!cmd.empty()) cmd += " ";
        cmd += arg;
    }
    
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        result.status = core::SemanticStatus::kFailure;
        result.error_message = "Failed to execute command";
        return result;
    }
    
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        if (result.stdout_data.size() + strlen(buffer) <= max_output_size) {
            result.stdout_data += buffer;
        } else {
            result.output_truncated = true;
            break;
        }
    }
    
    int exit_code = pclose(pipe);
    
    auto end_time = std::chrono::steady_clock::now();
    result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    if (WIFEXITED(exit_code)) {
        result.exit_code = WEXITSTATUS(exit_code);
        result.status = core::SemanticStatus::kCompleted;
    } else if (WIFSIGNALED(exit_code)) {
        result.exit_code = WTERMSIG(exit_code);
        result.status = core::SemanticStatus::kFailure;
    }
    
    // Check for timeout
    if (timeout.has_value() && result.duration_ms > *timeout) {
        result.timed_out = true;
        result.outcome = ProviderExecutionOutcome::kTimeout;
    } else {
        result.outcome = ProviderExecutionOutcome::kSuccess;
    }
    
    return result;
}

inline IPCFixture::IPCFixture(TestEnvironmentConfig config)
    : config_(std::move(config))
    , temp_dir_([this]() -> std::filesystem::path {
        static int counter = 0;
        auto dir = config_.temp_root / "ipc-" + std::to_string(counter++);
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        return dir;
    }()) {
}

inline IPCFixture::~IPCFixture() {
    // temp_dir_ handles cleanup
}

inline IPCFixture::IPCFixture(IPCFixture&&) noexcept = default;
inline IPCFixture& IPCFixture::operator=(IPCFixture&&) noexcept = default;

inline std::filesystem::path IPCFixture::create_unix_socket() {
    auto path = temp_dir_.path() / ("socket-" + std::to_string(time(nullptr)));
    
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) return {};
    
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);
    
    if (bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        close(fd);
        return {};
    }
    
    chmod(path.c_str(), 0600);
    close(fd);
    
    return path;
}

}  // namespace rebuntu::testing