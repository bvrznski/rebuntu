#pragma once
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace rebuntu::security::privilege_boundary_secure_execution {

enum class OperationKind { ServiceStart, ServiceStop, ServiceEnable, ServiceDisable, Mount, Unmount, NetworkLinkUp, NetworkLinkDown, PackageInstall, PackageRemove, ConfigWrite, ConfigRestore };
enum class RejectReason { None, Oversize, UnknownOperation, InvalidTarget, MissingAuthorization, StaleAuthorization, PeerMismatch, ResourceExhausted, Cancelled };
struct PeerIdentity { std::uint32_t uid{}; std::uint32_t gid{}; std::uint32_t pid{}; std::uint64_t start_ticks{}; };
struct AuthorizationBinding { std::string operation_fingerprint; std::string principal; std::uint64_t generation{}; bool allowed{}; };
struct SecureRequest { std::string request_id; OperationKind kind{}; std::string target; std::string payload; std::string operation_fingerprint; std::uint64_t authorization_generation{}; };
struct BoundaryLimits { std::size_t max_message_bytes{64*1024}; std::size_t max_payload_bytes{48*1024}; std::size_t max_inflight{128}; std::size_t max_target_bytes{4096}; };
struct ValidationResult { bool accepted{}; RejectReason reason{RejectReason::None}; std::string public_error; };

class SecureBoundary final {
public:
 explicit SecureBoundary(BoundaryLimits limits = {});
 [[nodiscard]] ValidationResult validate(const SecureRequest&, const PeerIdentity&, const PeerIdentity&, const AuthorizationBinding&, std::size_t inflight) const;
 [[nodiscard]] static bool safe_target(std::string_view target) noexcept;
 [[nodiscard]] static std::string redact_error(std::string_view text);
private: BoundaryLimits limits_;
};

class CancellationRegistry final {
public:
 bool begin(std::string id); bool cancel(std::string_view id); bool cancelled(std::string_view id) const; void finish(std::string_view id);
private: std::unordered_map<std::string,bool> requests_;
};

class RestartBudget final {
public:
 RestartBudget(std::size_t max_restarts, std::chrono::milliseconds window, std::chrono::milliseconds base_backoff);
 bool record_crash(std::chrono::steady_clock::time_point now);
 [[nodiscard]] std::chrono::milliseconds backoff() const noexcept;
 void record_healthy();
private:
 std::size_t max_; std::chrono::milliseconds window_, base_; std::vector<std::chrono::steady_clock::time_point> crashes_; std::size_t consecutive_{};
};

struct FdPolicy { std::unordered_set<int> allowed{0,1,2}; bool close_unknown{true}; };
[[nodiscard]] std::vector<int> descriptors_to_close(const std::vector<int>& open_fds, const FdPolicy& policy);
}
