#pragma once
#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <vector>
namespace rebuntu::security::privilege_boundary_secure_execution {
struct MessageFrame { std::uint16_t version{1}; std::uint16_t type{}; std::vector<std::byte> payload; };
class MessageFramer { public: explicit MessageFramer(std::size_t max_payload):max_(max_payload){}; [[nodiscard]] std::optional<std::vector<std::byte>> encode(const MessageFrame&) const; [[nodiscard]] std::optional<MessageFrame> decode(std::span<const std::byte>) const; private: std::size_t max_; };
}
