// rebuntu::semantic::ipc - Client-side IPC bindings (Phase 3.4)
//
// This implements the client-side interface for Rebuntu's semantic service IPC:
//   - Unix domain socket connection management
//   - Request/response correlation
//   - Timeout enforcement
//   - Error handling and validation

#include <system/semantic/ipc.hpp>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <poll.h>
#include <cstring>
#include <cerrno>

namespace rebuntu::semantic {

namespace {

// Create a Unix domain socket client
class UnixDomainSocketIPCClient : public SemanticIPCClient {
public:
    explicit UnixDomainSocketIPCClient(std::string socket_path)
        : socket_path_(std::move(socket_path)), socket_fd_(-1) {}

    ~UnixDomainSocketIPCClient() override {
        disconnect();
    }

    bool connect(std::chrono::milliseconds timeout) override {
        if (socket_fd_ >= 0) return true;  // Already connected

        // Create Unix domain socket
        socket_fd_ = ::socket(AF_UNIX, SOCK_STREAM, 0);
        if (socket_fd_ < 0) {
            return false;
        }

        // Set non-blocking for timeout
        int flags = fcntl(socket_fd_, F_GETFL, 0);
        if (flags >= 0) {
            fcntl(socket_fd_, F_SETFL, flags | O_NONBLOCK);
        }

        // Set up address structure
        sockaddr_un addr{};
        addr.sun_family = AF_UNIX;
        std::strncpy(addr.sun_path, socket_path_.c_str(), sizeof(addr.sun_path) - 1);

        // Connect with timeout using poll()
        int result = ::connect(socket_fd_, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
        
        if (result < 0) {
            if (errno == EINPROGRESS || errno == EWOULDBLOCK) {
                // Wait for connection to complete
                pollfd pfd{socket_fd_, POLLOUT, 0};
                int ret = ::poll(&pfd, 1, static_cast<int>(timeout.count()));
                
                if (ret <= 0) {
                    disconnect();
                    return false;
                }

                // Check for connection errors
                int so_error = 0;
                socklen_t len = sizeof(so_error);
                getsockopt(socket_fd_, SOL_SOCKET, SO_ERROR, &so_error, &len);
                
                if (so_error != 0) {
                    disconnect();
                    return false;
                }
            } else {
                close(socket_fd_);
                socket_fd_ = -1;
                return false;
            }
        }

        // Restore blocking mode
        if (flags >= 0) {
            fcntl(socket_fd_, F_SETFL, flags);
        }

        return true;
    }

    void disconnect() override {
        if (socket_fd_ >= 0) {
            ::close(socket_fd_);
            socket_fd_ = -1;
        }
    }

    bool is_connected() const override {
        return socket_fd_ >= 0;
    }

    std::optional<SemanticResponse> send_request(
        const SemanticRequest& request,
        std::chrono::milliseconds timeout
    ) override {
        if (socket_fd_ < 0) {
            return std::nullopt;
        }

        // Serialize the frame
        auto payload = serialize_request(request);
        
        SemanticFrame frame;
        frame.header.magic = kProtocolMagic;
        frame.header.version = kProtocolVersion;
        frame.header.frame_type = static_cast<uint16_t>(FrameType::kRequest);
        frame.header.correlation_id = request.correlations.request_id.empty() 
            ? 0 
            : std::stoull(request.correlations.request_id.substr(4));  // Extract counter from "req-XXXX"
        frame.header.payload_len = static_cast<uint32_t>(payload.size());
        frame.payload = std::move(payload);

        auto serialized = serialize_frame(frame);
        
        if (serialized.empty()) {
            return std::nullopt;
        }

        // Send the frame
        ssize_t sent = ::send(socket_fd_, serialized.data(), serialized.size(), 0);
        if (sent < 0) {
            return std::nullopt;
        }

        // Wait for response with timeout
        pollfd pfd{socket_fd_, POLLIN, 0};
        int ret = ::poll(&pfd, 1, static_cast<int>(timeout.count()));
        
        if (ret <= 0) {
            return std::nullopt;  // Timeout or error
        }

        // Read response header
        uint8_t header_buf[FrameHeader::kSize];
        ssize_t hdr_read = ::recv(socket_fd_, header_buf, FrameHeader::kSize, MSG_WAITALL);
        
        if (hdr_read < static_cast<ssize_t>(FrameHeader::kSize)) {
            return std::nullopt;
        }

        auto header_opt = parse_header(header_buf, FrameHeader::kSize);
        if (!header_opt.has_value()) {
            return std::nullopt;
        }

        // Read payload
        uint32_t payload_len = header_opt->payload_len;
        if (payload_len > kMaxPayloadSize) {
            return std::nullopt;
        }

        std::vector<uint8_t> payload_buf(payload_len);
        ssize_t payload_read = ::recv(socket_fd_, payload_buf.data(), payload_len, MSG_WAITALL);
        
        if (payload_read < static_cast<ssize_t>(payload_len)) {
            return std::nullopt;
        }

        // Deserialize response
        auto resp_opt = deserialize_response(payload_buf.data(), payload_buf.size());
        if (!resp_opt.has_value()) {
            return std::nullopt;
        }

        return resp_opt.value();
    }

    bool cancel_request(uint64_t correlation_id) override {
        if (socket_fd_ < 0) {
            return false;
        }

        SemanticFrame frame;
        frame.header.magic = kProtocolMagic;
        frame.header.version = kProtocolVersion;
        frame.header.frame_type = static_cast<uint16_t>(FrameType::kCancellation);
        frame.header.correlation_id = correlation_id;
        frame.header.payload_len = 0;

        auto serialized = serialize_frame(frame);
        
        if (serialized.empty()) {
            return false;
        }

        ssize_t sent = ::send(socket_fd_, serialized.data(), serialized.size(), 0);
        return sent > 0;
    }

private:
    std::string socket_path_;
    int socket_fd_;
};

}  // namespace

// Factory function to create an IPC client
std::unique_ptr<SemanticIPCClient> make_semantic_ipc_client(
    const std::string& socket_path) {
    
    return std::make_unique<UnixDomainSocketIPCClient>(socket_path);
}

}  // namespace rebuntu::semantic