// rebuntu::runtime::ipc — Inter-process communication grammar (Phase 0.15)
//
// This header establishes Rebuntu's IPC communication types independently
// of transport mechanism.

#pragma once

#include <runtime/core/contracts.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime::ipc {

enum class MessageKind {
    kEvent,
    kRequest,
    kResponse,
    kCommand,
};

inline std::string_view to_string(MessageKind kind) {
    switch (kind) {
        case MessageKind::kEvent: return "event";
        case MessageKind::kRequest: return "request";
        case MessageKind::kResponse: return "response";
        case MessageKind::kCommand: return "command";
    }
    return "unknown";
}

struct CorrelationIds {
    std::string request_id;
    std::optional<std::string> correlation_id;
    std::optional<std::string> causation_id;
};

struct Message {
    MessageKind kind;
    std::string id;
    CorrelationIds correlations;
    std::optional<std::string> source;
    std::optional<std::string> subject;
    std::vector<core::Evidence> evidence;
    std::optional<std::string> operation;
    std::optional<int64_t> timestamp_ns;
    bool reliable_delivery = false;
};

class Channel {
public:
    virtual ~Channel() = default;
    virtual bool send(Message msg) = 0;
    virtual std::optional<Message> receive(std::chrono::milliseconds timeout) = 0;
    virtual bool has_ready() const = 0;
    virtual void close() = 0;
    virtual size_t queue_size() const = 0;
};

enum class BackpressurePolicy {
    kBlock,
    kDropNewest,
    kDropOldest,
};

struct ChannelOptions {
    size_t max_buffer_size = 1024;
    BackpressurePolicy backpressure = BackpressurePolicy::kBlock;
    bool reliable_delivery = false;
};

enum class SelectedTransport { kInline, kUnixSocket, kDBus };

struct TransportDecision {
    SelectedTransport transport;
    std::string reason;
};

}  // namespace rebuntu::runtime::ipc
