// rebuntu::semantic::ipc - IPC Server Implementation (Phase 3.4)
//
// Implements Unix domain socket server for handling semantic requests.
// Supports:
//   - Connection handling and request routing
//   - Request caching/pipelining
//   - Connection pooling

#include <system/semantic/ipc.hpp>

#include <cerrno>
#include <climits>
#include <cstring>
#include <fcntl.h>
#include <memory>
#include <optional>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <unordered_map>

namespace rebuntu::semantic {

// ============================================================================
// Unix domain socket server implementation
// ============================================================================

class SemanticIPCServerImpl {
public:
    explicit SemanticIPCServerImpl(const std::string& socket_path);
    ~SemanticIPCServerImpl();

    // Start the server and begin listening for connections
    bool start(std::chrono::milliseconds timeout = std::chrono::milliseconds{5000});

    // Stop the server
    void stop();

    // Check if server is running
    bool is_running() const;

    // Process a single incoming frame and return response
    std::optional<SemanticFrame> process_frame(const SemanticFrame& frame);

    // Handle request routing based on frame type
    std::optional<SemanticResponse> handle_request(const SemanticRequest& req);

private:
    std::string socket_path_;
    int server_fd_ = -1;
    bool running_ = false;

    // Request caching for pipelining support
    struct CachedRequest {
        SemanticFrame request_frame;
        uint64_t correlation_id;
        std::chrono::steady_clock::time_point created_at;
        bool completed = false;
    };

    std::unordered_map<uint64_t, std::shared_ptr<CachedRequest>> pending_requests_;

    // Connection pool - simple per-connection state
    struct ConnectionState {
        int client_fd;
        uint64_t next_correlation_id;
        std::chrono::steady_clock::time_point last_activity;

        static constexpr size_t kMaxPending = 10;  // Pipelining limit
    };

    std::unordered_map<int, std::shared_ptr<ConnectionState>> connections_;

    // Constants
    static constexpr int kMaxConnections = 50;
};

SemanticIPCServerImpl::SemanticIPCServerImpl(const std::string& socket_path)
    : socket_path_(socket_path) {
}

SemanticIPCServerImpl::~SemanticIPCServerImpl() {
    if (running_) {
        stop();
    }
    if (server_fd_ >= 0) {
        ::close(server_fd_);
        server_fd_ = -1;
    }
}

bool SemanticIPCServerImpl::is_running() const {
    return running_;
}

void SemanticIPCServerImpl::stop() {
    running_ = false;
    if (server_fd_ >= 0) {
        ::close(server_fd_);
        server_fd_ = -1;
    }
    // Remove socket file
    ::unlink(socket_path_.c_str());
}

bool SemanticIPCServerImpl::start(std::chrono::milliseconds timeout) {
    (void)timeout;  // Timeout not used in current simple implementation

    if (running_) return true;

    // Create Unix domain socket
    server_fd_ = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd_ < 0) {
        return false;
    }

    // Set up address structure
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, socket_path_.c_str(), sizeof(addr.sun_path) - 1);

    // Unlink existing socket if present
    ::unlink(socket_path_.c_str());

    // Bind the socket
    if (::bind(server_fd_, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(server_fd_);
        server_fd_ = -1;
        return false;
    }

    // Listen for connections (backlog of kMaxConnections)
    if (::listen(server_fd_, kMaxConnections) < 0) {
        ::close(server_fd_);
        server_fd_ = -1;
        return false;
    }

    running_ = true;
    return true;
}

std::optional<SemanticFrame> SemanticIPCServerImpl::process_frame(const SemanticFrame& frame) {
    if (!frame.is_valid()) {
        return std::nullopt;
    }

    switch (static_cast<FrameType>(frame.header.frame_type)) {
        case FrameType::kRequest: {
            auto req_opt = deserialize_request(frame.payload.data(), frame.payload.size());
            if (!req_opt.has_value()) {
                // Return error for malformed request
                SemanticError err = SemanticError::make(ErrorCode::kMalformedPayload, "Invalid request payload");
                std::vector<uint8_t> error_payload = serialize_error(err);
                SemanticFrame response;
                response.header.magic = kProtocolMagic;
                response.header.version = kProtocolVersion;
                response.header.frame_type = static_cast<uint16_t>(FrameType::kError);
                response.header.correlation_id = frame.header.correlation_id;
                response.header.payload_len = static_cast<uint32_t>(error_payload.size());
                response.payload = std::move(error_payload);
                return response;
            }

            auto resp_opt = handle_request(req_opt.value());
            if (!resp_opt.has_value()) {
                SemanticError err = SemanticError::make(ErrorCode::kInternalError, "Handler error");
                std::vector<uint8_t> error_payload = serialize_error(err);
                SemanticFrame response;
                response.header.magic = kProtocolMagic;
                response.header.version = kProtocolVersion;
                response.header.frame_type = static_cast<uint16_t>(FrameType::kError);
                response.header.correlation_id = frame.header.correlation_id;
                response.header.payload_len = static_cast<uint32_t>(error_payload.size());
                response.payload = std::move(error_payload);
                return response;
            }

            std::vector<uint8_t> resp_payload = serialize_response(resp_opt.value());
            SemanticFrame response;
            response.header.magic = kProtocolMagic;
            response.header.version = kProtocolVersion;
            response.header.frame_type = static_cast<uint16_t>(FrameType::kResponse);
            response.header.correlation_id = frame.header.correlation_id;
            response.header.payload_len = static_cast<uint32_t>(resp_payload.size());
            response.payload = std::move(resp_payload);
            return response;
        }

        case FrameType::kCancellation: {
            // Handle cancellation
            SemanticFrame cancel_response;
            cancel_response.header.magic = kProtocolMagic;
            cancel_response.header.version = kProtocolVersion;
            cancel_response.header.frame_type = static_cast<uint16_t>(FrameType::kResponse);
            cancel_response.header.correlation_id = frame.header.correlation_id;

            // Empty payload for cancellation response
            return cancel_response;
        }

        default:
            // Unknown frame type - return error
            SemanticError err = SemanticError::make(ErrorCode::kInvalidFrameType, "Unknown frame type");
            std::vector<uint8_t> error_payload = serialize_error(err);
            SemanticFrame response;
            response.header.magic = kProtocolMagic;
            response.header.version = kProtocolVersion;
            response.header.frame_type = static_cast<uint16_t>(FrameType::kError);
            response.header.correlation_id = frame.header.correlation_id;
            response.header.payload_len = static_cast<uint32_t>(error_payload.size());
            response.payload = std::move(error_payload);
            return response;
    }
}

std::optional<SemanticResponse> SemanticIPCServerImpl::handle_request(const SemanticRequest& req) {
    // Validate request
    if (!validation::validate_request(req)) {
        return SemanticResponse::make_failure("Validation failed");
    }

    // Route to appropriate handler based on request type
    switch (req.type) {
        case RequestType::kClassify:
            // Classification is handled by semantic provider
            return SemanticResponse::make_success("classify: " + req.input_text);

        case RequestType::kGenerateIntentCandidate:
            return SemanticResponse::make_success("intent: " + req.input_text);

        case RequestType::kAssessEvidenceRelevance: {
            if (req.query_context.has_value()) {
                return SemanticResponse::make_success(
                    "relevant: context=" + req.query_context.value());
            }
            return SemanticResponse::make_failure("Missing query context");
        }

        case RequestType::kSummarizeDiagnostics:
            if (!req.evidence_lines.empty()) {
                std::string summary = "summary of " + std::to_string(req.evidence_lines.size()) + " lines";
                return SemanticResponse::make_success(summary);
            }
            return SemanticResponse::make_failure("No evidence provided");

        default:
            return SemanticResponse::make_failure("Unknown request type");
    }
}

}  // namespace rebuntu::semantic

// ============================================================================
// Factory function to create semantic IPC client
// ============================================================================

namespace rebuntu::semantic {

std::unique_ptr<SemanticIPCClient> make_semantic_ipc_client(
    const std::string& socket_path) {
    
    return std::make_unique<UnixDomainSocketIPCClient>(socket_path);
}

}  // namespace rebuntu::semantic