// rebuntu::semantic::ipc::transport — IPC Frame Serialization (Phase 3.4)
//
// This implements frame serialization and deserialization for Rebuntu's
// structured semantic IPC protocol.

#include <system/semantic/ipc.hpp>

#include <cstring>
#include <stdexcept>

namespace rebuntu::semantic::ipc {

// ============================================================================
// Helper: Write bytes in little-endian format
// ============================================================================

static void write_le16(uint8_t* dst, int16_t value) {
    dst[0] = static_cast<uint8_t>(value & 0xFF);
    dst[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

static void write_le32(uint8_t* dst, uint32_t value) {
    dst[0] = static_cast<uint8_t>(value & 0xFF);
    dst[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    dst[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    dst[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

static void write_le64(uint8_t* dst, uint64_t value) {
    dst[0] = static_cast<uint8_t>(value & 0xFF);
    dst[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    dst[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    dst[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
    dst[4] = static_cast<uint8_t>((value >> 32) & 0xFF);
    dst[5] = static_cast<uint8_t>((value >> 40) & 0xFF);
    dst[6] = static_cast<uint8_t>((value >> 48) & 0xFF);
    dst[7] = static_cast<uint8_t>((value >> 56) & 0xFF);
}

// ============================================================================
// Helper: Read bytes in little-endian format
// ============================================================================

static int16_t read_le16(const uint8_t* src) {
    return static_cast<int16_t>(
        (static_cast<uint16_t>(src[0])) |
        (static_cast<uint16_t>(src[1]) << 8)
    );
}

static uint32_t read_le32(const uint8_t* src) {
    return static_cast<uint32_t>(
        (static_cast<uint32_t>(src[0])) |
        (static_cast<uint32_t>(src[1]) << 8) |
        (static_cast<uint32_t>(src[2]) << 16) |
        (static_cast<uint32_t>(src[3]) << 24)
    );
}

static uint64_t read_le64(const uint8_t* src) {
    return static_cast<uint64_t>(
        (static_cast<uint64_t>(src[0])) |
        (static_cast<uint64_t>(src[1]) << 8) |
        (static_cast<uint64_t>(src[2]) << 16) |
        (static_cast<uint64_t>(src[3]) << 24) |
        (static_cast<uint64_t>(src[4]) << 32) |
        (static_cast<uint64_t>(src[5]) << 40) |
        (static_cast<uint64_t>(src[6]) << 48) |
        (static_cast<uint64_t>(src[7]) << 56)
    );
}

// ============================================================================
// Helper: String length encoding (length-prefixed with uint32)
// ============================================================================

static size_t encoded_string_size(const std::string& s) {
    return sizeof(uint32_t) + s.size();
}

static void write_encoded_string(std::vector<uint8_t>& out, const std::string& s) {
    // Limit string length for safety
    if (s.size() > kMaxStringFieldLength) {
        throw std::runtime_error("String exceeds maximum allowed length");
    }
    
    uint32_t len = static_cast<uint32_t>(s.size());
    size_t old_size = out.size();
    out.resize(old_size + encoded_string_size(s));
    write_le32(out.data() + old_size, len);
    std::memcpy(out.data() + old_size + sizeof(uint32_t), s.data(), s.size());
}

static std::optional<std::string> read_encoded_string(
    const uint8_t* data, size_t len, size_t& pos
) {
    if (pos + sizeof(uint32_t) > len) {
        return std::nullopt;
    }
    
    uint32_t str_len = read_le32(data + pos);
    pos += sizeof(uint32_t);
    
    if (str_len > kMaxStringFieldLength || pos + str_len > len) {
        return std::nullopt;
    }
    
    std::string result(reinterpret_cast<const char*>(data + pos), str_len);
    pos += str_len;
    return result;
}

// ============================================================================
// Frame serialization
// ============================================================================

std::vector<uint8_t> serialize_frame(const Frame& frame) {
    std::vector<uint8_t> out;
    
    // Reserve space for header (20 bytes)
    size_t header_pos = out.size();
    out.resize(header_pos + sizeof(FrameHeader));
    
    // Write header fields
    write_le32(out.data() + header_pos, FrameHeader::kMagic);
    write_le16(out.data() + header_pos + 4, frame.header.version);
    write_le16(out.data() + header_pos + 6, static_cast<int16_t>(frame.frame_type()));
    write_le64(out.data() + header_pos + 8, frame.header.correlation.value);
    // payload_length will be filled after we know the size
    
    // Serialize payload based on frame type
    size_t payload_start = out.size();
    
    switch (frame.frame_type()) {
        case FrameType::kRequest: {
            if (!frame.request.has_value()) {
                return std::vector<uint8_t>();  // Invalid request
            }
            
            write_le16(out.data() + payload_start, static_cast<int16_t>(frame.request->type));
            size_t offset = 2;
            
            // Timestamp (as unix timestamp in ms)
            auto ts_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(
                frame.request->timestamp
            );
            write_le64(out.data() + payload_start + offset, 
                       static_cast<uint64_t>(ts_ms.time_since_epoch().count()));
            offset += 8;
            
            // Timeout (optional)
            if (frame.request->timeout_ms.has_value()) {
                out[payload_start + offset] = 1;  // present flag
                write_le64(out.data() + payload_start + offset + 1,
                           static_cast<uint64_t>(frame.request->timeout_ms.value().count()));
                offset += 9;
            } else {
                out[payload_start + offset] = 0;  // not present
                offset += 1;
            }
            
            // Type-specific data based on request type
            switch (frame.request->type) {
                case RequestType::kClassification: {
                    if (!frame.request->classification.has_value()) break;
                    
                    write_le16(out.data() + payload_start + offset, 1);  // classification tag
                    offset += 2;
                    
                    const auto& cd = frame.request->classification.value();
                    write_encoded_string(out, cd.input);
                    
                    uint16_t num_cats = static_cast<uint16_t>(
                        std::min(cd.categories.size(), kMaxCategories)
                    );
                    write_le16(out.data() + out.size(), num_cats);
                    size_t cats_start = out.size() - 2;
                    for (size_t i = 0; i < num_cats && i < cd.categories.size(); ++i) {
                        write_encoded_string(out, cd.categories[i]);
                    }
                    // Update the count with actual written categories
                    uint16_t actual_count = static_cast<uint16_t>(out.size() - cats_start - 2);
                    if (actual_count > num_cats * sizeof(uint32_t)) {
                        // Count is at offset 0, string data follows
                        write_le16(out.data() + cats_start + 2, actual_count / 4);  // approx
                    }
                    break;
                }
                
                case RequestType::kIntentCandidate: {
                    if (!frame.request->intent_candidate.has_value()) break;
                    
                    write_le16(out.data() + payload_start + offset, 2);  // intent tag
                    offset += 2;
                    
                    const auto& icd = frame.request->intent_candidate.value();
                    write_encoded_string(out, icd.input);
                    
                    uint16_t num_ops = static_cast<uint16_t>(
                        std::min(icd.allowed_operations.size(), kMaxCategories)
                    );
                    write_le16(out.data() + out.size(), num_ops);
                    size_t ops_start = out.size() - 2;
                    for (size_t i = 0; i < num_ops && i < icd.allowed_operations.size(); ++i) {
                        write_encoded_string(out, icd.allowed_operations[i]);
                    }
                    break;
                }
                
                case RequestType::kEvidenceRelevance: {
                    if (!frame.request->evidence_relevance.has_value()) break;
                    
                    write_le16(out.data() + payload_start + offset, 3);  // evidence tag
                    offset += 2;
                    
                    const auto& erd = frame.request->evidence_relevance.value();
                    write_encoded_string(out, erd.evidence);
                    write_encoded_string(out, erd.context);
                    break;
                }
                
                case RequestType::kDiagnosticSummary: {
                    if (!frame.request->diagnostic_summary.has_value()) break;
                    
                    write_le16(out.data() + payload_start + offset, 4);  // summary tag
                    offset += 2;
                    
                    const auto& dsd = frame.request->diagnostic_summary.value();
                    uint16_t num_items = static_cast<uint16_t>(
                        std::min(dsd.diagnostic_items.size(), kMaxDiagnosticItems)
                    );
                    write_le16(out.data() + out.size(), num_items);
                    
                    for (size_t i = 0; i < num_items && i < dsd.diagnostic_items.size(); ++i) {
                        write_encoded_string(out, dsd.diagnostic_items[i]);
                    }
                    break;
                }
            }
            
            break;
        }
        
        case FrameType::kResponse: {
            if (!frame.response.has_value()) {
                return std::vector<uint8_t>();  // Invalid response
            }
            
            write_le16(out.data() + payload_start, static_cast<int16_t>(frame.response->type));
            size_t offset = 2;
            
            // Responded at timestamp
            auto ts_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(
                frame.response->responded_at
            );
            write_le64(out.data() + payload_start + offset,
                       static_cast<uint64_t>(ts_ms.time_since_epoch().count()));
            offset += 8;
            
            // Inference time (optional)
            if (frame.response->inference_time_ms.has_value()) {
                out[payload_start + offset] = 1;
                write_le64(out.data() + payload_start + offset + 1,
                           static_cast<uint64_t>(frame.response->inference_time_ms.value().count()));
                offset += 9;
            } else {
                out[payload_start + offset] = 0;
                offset += 1;
            }
            
            // Provider ID
            write_encoded_string(out, frame.response->provider_id);
            
            // Type-specific response data (simplified)
            switch (frame.response->type) {
                case ResponseType::kClassification: {
                    if (!frame.response->classification.has_value()) break;
                    
                    uint16_t num_cats = static_cast<uint16_t>(
                        std::min(frame.response->classification->categories.size(), kMaxCategories)
                    );
                    write_le16(out.data() + out.size(), num_cats);
                    size_t cats_start = out.size() - 2;
                    
                    for (size_t i = 0; i < num_cats && i < frame.response->classification->categories.size(); ++i) {
                        const auto& cat = frame.response->classification->categories[i];
                        write_encoded_string(out, cat.first);
                        
                        // Encode confidence as uint32_t (multiplied by 1000)
                        uint32_t conf_val = static_cast<uint32_t>(cat.second * 1000.0);
                        out.push_back(static_cast<uint8_t>(conf_val & 0xFF));
                        out.push_back(static_cast<uint8_t>((conf_val >> 8) & 0xFF));
                        out.push_back(static_cast<uint8_t>((conf_val >> 16) & 0xFF));
                        out.push_back(static_cast<uint8_t>((conf_val >> 24) & 0xFF));
                    }
                    break;
                }
                
                case ResponseType::kIntentCandidate: {
                    if (!frame.response->intent_candidate.has_value()) break;
                    
                    const auto& ic = frame.response->intent_candidate.value();
                    write_encoded_string(out, ic.operation_id);
                    
                    // Subject (optional)
                    out.push_back(ic.subject.has_value() ? 1 : 0);
                    if (ic.subject.has_value()) {
                        write_encoded_string(out, ic.subject.value());
                    }
                    
                    // Parameters
                    uint16_t num_params = static_cast<uint16_t>(
                        std::min(ic.parameters.size(), kMaxCategories)
                    );
                    write_le16(out.data() + out.size(), num_params);
                    size_t params_start = out.size() - 2;
                    
                    for (size_t i = 0; i < num_params && i < ic.parameters.size(); ++i) {
                        auto it = std::next(ic.parameters.begin(), i);
                        write_encoded_string(out, it->first);
                        write_encoded_string(out, it->second);
                    }
                    
                    // Confidence
                    uint32_t conf_val = static_cast<uint32_t>(ic.confidence * 1000.0);
                    out.push_back(static_cast<uint8_t>(conf_val & 0xFF));
                    out.push_back(static_cast<uint8_t>((conf_val >> 8) & 0xFF));
                    out.push_back(static_cast<uint8_t>((conf_val >> 16) & 0xFF));
                    out.push_back(static_cast<uint8_t>((conf_val >> 24) & 0xFF));
                    break;
                }
                
                case ResponseType::kEvidenceRelevance: {
                    if (!frame.response->relevance.has_value()) break;
                    
                    const auto& er = frame.response->relevance.value();
                    out.push_back(er.is_relevant ? 1 : 0);
                    
                    // Relevance score (optional)
                    out.push_back(er.relevance_score.has_value() ? 1 : 0);
                    if (er.relevance_score.has_value()) {
                        uint32_t score_val = static_cast<uint32_t>(er.relevance_score.value() * 1000.0);
                        write_le32(out.data() + out.size(), score_val);
                        out.resize(out.size() + 4);
                    }
                    
                    if (er.explanation.has_value()) {
                        write_encoded_string(out, er.explanation.value());
                    }
                    break;
                }
                
                case ResponseType::kDiagnosticSummary: {
                    if (!frame.response->summary.has_value()) break;
                    
                    const auto& ds = frame.response->summary.value();
                    write_encoded_string(out, ds.summary);
                    
                    uint16_t num_findings = static_cast<uint16_t>(
                        std::min(ds.key_findings.size(), kMaxDiagnosticItems)
                    );
                    write_le16(out.data() + out.size(), num_findings);
                    
                    for (size_t i = 0; i < num_findings && i < ds.key_findings.size(); ++i) {
                        write_encoded_string(out, ds.key_findings[i]);
                    }
                    
                    // Suggested action (optional)
                    out.push_back(ds.suggested_action.has_value() ? 1 : 0);
                    if (ds.suggested_action.has_value()) {
                        write_encoded_string(out, ds.suggested_action.value());
                    }
                    break;
                }
                
                default:
                    break;
            }
            
            break;
        }
        
        case FrameType::kError: {
            if (!frame.error.has_value()) {
                return std::vector<uint8_t>();  // Invalid error
            }
            
            write_le16(out.data() + payload_start, static_cast<int16_t>(frame.error->code));
            write_encoded_string(out, frame.error->message);
            
            // Related correlation (optional)
            if (frame.error->related_correlation.value != 0) {
                out.push_back(1);  // present flag
                write_le64(out.data() + out.size(), frame.error->related_correlation.value);
                out.resize(out.size() + 8);
            } else {
                out.push_back(0);  // not present
            }
            
            break;
        }
        
        case FrameType::kCancellation: {
            if (!frame.cancellation.has_value()) {
                return std::vector<uint8_t>();  // Invalid cancellation
            }
            
            write_le64(out.data() + payload_start, 
                      frame.cancellation->target.value);
            break;
        }
    }
    
    // Fill in the payload length
    uint32_t payload_len = static_cast<uint32_t>(out.size() - payload_start);
    write_le32(out.data() + header_pos + 16, payload_len);
    
    return out;
}

// ============================================================================
// Frame parsing (basic implementation)
// ============================================================================

std::optional<Frame> parse_frame(const std::vector<uint8_t>& data) {
    if (data.size() < sizeof(FrameHeader)) {
        return std::nullopt;
    }
    
    Frame frame;
    size_t pos = 0;
    
    // Read magic
    uint32_t magic = read_le32(data.data());
    if (magic != FrameHeader::kMagic) {
        return std::nullopt;
    }
    frame.header.magic = magic;
    pos += sizeof(uint32_t);
    
    // Read version
    frame.header.version = read_le16(data.data() + pos);
    pos += sizeof(int16_t);
    
    // Read frame type
    int16_t ft_raw = read_le16(data.data() + pos);
    pos += sizeof(int16_t);
    frame.header.frame_type = ft_raw;
    
    // Read correlation ID
    frame.header.correlation.value = read_le64(data.data() + pos);
    pos += sizeof(uint64_t);
    
    // Read payload length
    frame.header.payload_length = read_le32(data.data() + pos);
    pos += sizeof(uint32_t);
    
    if (frame.header.payload_length == 0 || 
        data.size() < pos + frame.header.payload_length) {
        return frame;  // Empty frame or truncated
    }
    
    const uint8_t* payload = data.data() + pos;
    size_t payload_len = frame.header.payload_length;
    
    // Parse payload based on frame type
    switch (frame.frame_type()) {
        case FrameType::kRequest: {
            if (payload_len < 2) return std::nullopt;
            
            RequestType rt = static_cast<RequestType>(read_le16(payload));
            pos += 2;
            
            SemanticRequestPayload req;
            req.type = rt;
            
            // Timestamp
            if (pos + 8 <= payload_len) {
                auto epoch_ms = read_le64(payload + pos);
                req.timestamp = std::chrono::system_clock::from_time_t(epoch_ms / 1000);
                pos += 8;
            }
            
            // Timeout (if present)
            if (pos < payload_len && payload[pos] == 1) {
                pos++;
                if (pos + 8 <= payload_len) {
                    auto timeout_ms = read_le64(payload + pos);
                    req.timeout_ms = std::chrono::milliseconds(timeout_ms);
                    pos += 8;
                }
            } else if (pos < payload_len) {
                pos++;  // skip present flag
            }
            
            frame.request = req;
            
            break;
        }
        
        case FrameType::kResponse: {
            if (payload_len < 2) return std::nullopt;
            
            ResponseType rt = static_cast<ResponseType>(read_le16(payload));
            pos += 2;
            
            SemanticResponsePayload resp;
            resp.type = rt;
            
            // Responded at timestamp
            if (pos + 8 <= payload_len) {
                auto epoch_ms = read_le64(payload + pos);
                resp.responded_at = std::chrono::system_clock::from_time_t(epoch_ms / 1000);
                pos += 8;
            }
            
            // Provider ID
            auto provider_opt = read_encoded_string(payload, payload_len, pos);
            if (provider_opt) {
                resp.provider_id = *provider_opt;
            }
            
            frame.response = resp;
            
            break;
        }
        
        case FrameType::kError: {
            if (payload_len < 2) return std::nullopt;
            
            ErrorPayload err;
            err.code = static_cast<ErrorCode>(read_le16(payload));
            pos += 2;
            
            auto msg_opt = read_encoded_string(payload, payload_len, pos);
            if (msg_opt) {
                err.message = *msg_opt;
            }
            
            frame.error = err;
            
            break;
        }
        
        case FrameType::kCancellation: {
            if (payload_len < 8) return std::nullopt;
            
            CancellationPayload cancel;
            cancel.target.value = read_le64(payload);
            pos += 8;
            
            frame.cancellation = cancel;
            
            break;
        }
    }
    
    return frame;
}

std::optional<size_t> get_expected_frame_size(const uint8_t* data, size_t len) {
    if (len < sizeof(FrameHeader)) {
        return std::nullopt;
    }
    
    // Check magic
    if (read_le32(data) != FrameHeader::kMagic) {
        return std::nullopt;
    }
    
    // Read payload length from header
    size_t header_payload_offset = 16;  // After magic(4), version(2), frame_type(2), correlation(8)
    uint32_t payload_len = read_le32(data + header_payload_offset);
    
    return sizeof(FrameHeader) + payload_len;
}

}  // namespace rebuntu::semantic::ipc