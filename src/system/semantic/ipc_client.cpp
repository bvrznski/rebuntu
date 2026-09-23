// rebuntu::semantic::ipc::client — IPC Client Bindings (Phase 3.4)
//
// This implements the client-side bindings for Rebuntu's structured semantic
// IPC protocol, providing a typed interface to the Unix domain socket transport.

#include <system/semantic/ipc.hpp>

#include <cerrno>
#include <cstring>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>

namespace rebuntu::semantic::ipc {

// ============================================================================
// Frame-based client connection
// ============================================================================

class SemanticIpcClient {
public:
    explicit SemanticIpcClient(std::filesystem::path socket_path)
        : socket_path_(std::move(socket_path)) {}
    
    ~SemanticIpcClient() = default;
    
    // Try to connect to the semantic service
    bool connect(
        std::chrono::milliseconds timeout = std::chrono::seconds(5)
    ) {
        if (is_connected_) {
            return true;  // Already connected
        }
        
        // Create socket
        socket_fd_ = ::socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
        if (socket_fd_ < 0) {
            return false;
        }
        
        // Set timeout on socket
        struct timeval tv;
        tv.tv_sec = timeout.count() / 1000;
        tv.tv_usec = (timeout.count() % 1000) * 1000;
        ::setsockopt(socket_fd_, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
        ::setsockopt(socket_fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        
        // Connect to the server
        struct sockaddr_un addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        
        std::string path_str = socket_path_.string();
        if (path_str.size() >= sizeof(addr.sun_path)) {
            ::close(socket_fd_);
            socket_fd_ = -1;
            return false;  // Path too long
        }
        std::strncpy(addr.sun_path, path_str.c_str(), sizeof(addr.sun_path) - 1);
        
        int ret = ::connect(socket_fd_, 
                           reinterpret_cast<struct sockaddr*>(&addr), 
                           sizeof(addr));
        if (ret < 0) {
            ::close(socket_fd_);
            socket_fd_ = -1;
            return false;
        }
        
        is_connected_ = true;
        return true;
    }
    
    // Send a frame and receive response
    std::optional<Frame> send_and_recv_frame(const Frame& request, 
                                              std::chrono::milliseconds timeout) {
        if (!is_connected_) {
            if (!connect(timeout)) {
                return std::nullopt;
            }
        }
        
        // Serialize and send the request
        auto serialized = serialize_frame(request);
        if (serialized.empty()) {
            return std::nullopt;
        }
        
        ssize_t sent = ::send(socket_fd_, serialized.data(), serialized.size(), 0);
        if (sent < 0) {
            return std::nullopt;
        }
        
        // Receive response with timeout
        struct pollfd pfd = {socket_fd_, POLLIN, 0};
        int ret = ::poll(&pfd, 1, timeout.count());
        
        if (ret <= 0) {
            return std::nullopt;  // Timeout or error
        }
        
        // Read header first
        uint8_t header_buffer[sizeof(FrameHeader)];
        ssize_t read_size = ::recv(socket_fd_, header_buffer, sizeof(FrameHeader), MSG_WAITALL);
        
        if (read_size < static_cast<ssize_t>(sizeof(FrameHeader))) {
            return std::nullopt;  // Incomplete header or error
        }
        
        // Parse and receive full frame
        auto frame_opt = parse_frame(header_buffer, sizeof(FrameHeader));
        if (!frame_opt) {
            return std::nullopt;
        }
        
        return frame_opt;
    }
    
    // Send a classification request and wait for response
    std::optional<SemanticResponsePayload> send_classification(
        const SemanticRequestPayload& request,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)
    ) {
        if (!connect(timeout)) {
            return std::nullopt;
        }
        
        CorrelationId corr = CorrelationId::generate();
        
        Frame frame;
        frame.header.magic = FrameHeader::kMagic;
        frame.header.version = kProtocolVersion;
        frame.header.frame_type = static_cast<int16_t>(FrameType::kRequest);
        frame.header.correlation = corr;
        frame.request = request;
        
        auto response_frame = send_and_recv_frame(frame, timeout);
        if (!response_frame.has_value() || 
            response_frame->frame_type() != FrameType::kResponse) {
            return std::nullopt;
        }
        
        return response_frame->response;
    }
    
private:
    std::filesystem::path socket_path_;
    int socket_fd_ = -1;
    bool is_connected_ = false;
    
    // Helper to parse a frame from received data
    std::optional<Frame> parse_frame(const uint8_t* data, size_t len) {
        if (len < sizeof(FrameHeader)) {
            return std::nullopt;
        }
        
        Frame frame;
        size_t pos = 0;
        
        // Read magic
        uint32_t magic = read_le32(data);
        if (magic != FrameHeader::kMagic) {
            return std::nullopt;
        }
        frame.header.magic = magic;
        pos += sizeof(uint32_t);
        
        // Read version
        frame.header.version = read_le16(data + pos);
        pos += sizeof(int16_t);
        
        // Read frame type
        int16_t ft_raw = read_le16(data + pos);
        pos += sizeof(int16_t);
        frame.header.frame_type = ft_raw;
        
        // Read correlation ID
        frame.header.correlation.value = read_le64(data + pos);
        pos += sizeof(uint64_t);
        
        // Read payload length
        frame.header.payload_length = read_le32(data + pos);
        pos += sizeof(uint32_t);
        
        if (frame.header.payload_length == 0) {
            return frame;  // Empty frame
        }
        
        // Read and parse the rest of the header from data
        const uint8_t* payload_start = data + pos;
        
        // Parse payload based on frame type
        switch (frame.frame_type()) {
            case FrameType::kRequest: {
                if (pos + 2 > len) return std::nullopt;
                
                RequestType rt = static_cast<RequestType>(read_le16(payload_start));
                pos += 2;
                
                SemanticRequestPayload req;
                req.type = rt;
                
                // Timestamp
                if (pos + 8 <= len) {
                    auto epoch_ms = read_le64(payload_start + pos);
                    req.timestamp = std::chrono::system_clock::from_time_t(epoch_ms / 1000);
                    pos += 8;
                }
                
                frame.request = req;
                break;
            }
            
            case FrameType::kResponse: {
                if (pos + 2 > len) return std::nullopt;
                
                ResponseType rt = static_cast<ResponseType>(read_le16(payload_start));
                pos += 2;
                
                SemanticResponsePayload resp;
                resp.type = rt;
                
                // Responded at timestamp
                if (pos + 8 <= len) {
                    auto epoch_ms = read_le64(payload_start + pos);
                    resp.responded_at = std::chrono::system_clock::from_time_t(epoch_ms / 1000);
                    pos += 8;
                }
                
                // Provider ID
                size_t tmp_pos = pos;
                if (tmp_pos + 4 <= len) {
                    uint32_t str_len = read_le32(payload_start + tmp_pos);
                    tmp_pos += 4;
                    if (tmp_pos + str_len <= len) {
                        resp.provider_id.assign(
                            reinterpret_cast<const char*>(payload_start + tmp_pos),
                            str_len
                        );
                        pos = tmp_pos + str_len;
                    }
                }
                
                frame.response = resp;
                break;
            }
            
            case FrameType::kError: {
                if (pos + 2 > len) return std::nullopt;
                
                ErrorPayload err;
                err.code = static_cast<ErrorCode>(read_le16(payload_start));
                pos += 2;
                
                // Message
                size_t tmp_pos = pos;
                if (tmp_pos + 4 <= len) {
                    uint32_t str_len = read_le32(payload_start + tmp_pos);
                    tmp_pos += 4;
                    if (tmp_pos + str_len <= len) {
                        err.message.assign(
                            reinterpret_cast<const char*>(payload_start + tmp_pos),
                            str_len
                        );
                        pos = tmp_pos + str_len;
                    }
                }
                
                frame.error = err;
                break;
            }
            
            case FrameType::kCancellation: {
                if (pos + 8 > len) return std::nullopt;
                
                CancellationPayload cancel;
                cancel.target.value = read_le64(payload_start);
                pos += 8;
                
                frame.cancellation = cancel;
                break;
            }
        }
        
        return frame;
    }
    
    static uint32_t read_le32(const uint8_t* src) {
        return (static_cast<uint32_t>(src[0])) |
               (static_cast<uint32_t>(src[1]) << 8) |
               (static_cast<uint32_t>(src[2]) << 16) |
               (static_cast<uint32_t>(src[3]) << 24);
    }
    
    static int16_t read_le16(const uint8_t* src) {
        return static_cast<int16_t>(
            (static_cast<uint16_t>(src[0])) |
            (static_cast<uint16_t>(src[1]) << 8)
        );
    }
    
    static uint64_t read_le64(const uint8_t* src) {
        return (static_cast<uint64_t>(src[0])) |
               (static_cast<uint64_t>(src[1]) << 8) |
               (static_cast<uint64_t>(src[2]) << 16) |
               (static_cast<uint64_t>(src[3]) << 24) |
               (static_cast<uint64_t>(src[4]) << 32) |
               (static_cast<uint64_t>(src[5]) << 40) |
               (static_cast<uint64_t>(src[6]) << 48) |
               (static_cast<uint64_t>(src[7]) << 56);
    }
};

}  // namespace rebuntu::semantic::ipc