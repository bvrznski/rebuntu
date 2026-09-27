// rebuntu::shell::values — Typed Value Parsers (Phase 6.6)
//
// This module defines typed value parsers for recurring command-line argument types:
//
//   - Duration: "30s", "5m", "2h" -> std::chrono::milliseconds
//   - ByteSize: "1K", "2MB", "1GB" -> uint64_t bytes
//   - Path: Filesystem paths with proper quoting and glob handling
//   - Identifier: Valid identifiers (no special chars)
//   - Enum: String to enum conversion with validation
//   - Boolean: "true"/"false"/"yes"/"no"/"1"/"0"
//   - List: Comma-separated or space-separated lists
//
// Design Principles:
//   * Parsers produce typed values, not strings
//   * Errors include exact position and expected format
//   * No side effects during parsing
//   * Shell globbing is preserved as input (not expanded)
//   * Paths can begin with '-' without being treated as options

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <type_traits>

namespace rebuntu::shell::values {

// ============================================================================
// ParseError — Parsing failures with context
// ============================================================================

struct ParseError {
    std::string message;
    size_t position{0};  // Character position where error occurred
    std::optional<std::string> expected;  // What was expected
    
    static ParseError invalid(std::string_view /*input*/, std::string_view expected_format) {
        ParseError e;
        e.message = "invalid " + std::string(expected_format);
        return e;
    }
    
    static ParseError unexpected_end(std::string_view /*input*/, size_t pos) {
        ParseError e;
        e.message = "unexpected end of input";
        e.position = pos;
        e.expected = "more input";
        return e;
    }
};

// ============================================================================
// DurationParser — Parse duration strings to std::chrono::milliseconds
//
// Supported formats:
//   - "30s" or "30sec" or "30seconds" -> 30000ms
//   - "5m" or "5min" or "5minutes" -> 300000ms
//   - "2h" or "2hour" or "2hours" -> 7200000ms
//   - "150ms" or "150msec" -> 150ms
// ============================================================================

struct DurationParser {
    using value_type = std::chrono::milliseconds;
    
    // Parse a duration string, returns nullopt on error
    static std::optional<value_type> parse(std::string_view input) noexcept {
        if (input.empty()) return std::nullopt;
        
        size_t i = 0;
        
        // Skip leading whitespace
        while (i < input.size() && std::isspace(input[i])) i++;
        
        // Parse numeric part
        size_t num_start = i;
        bool has_dot = false;
        while (i < input.size()) {
            char c = input[i];
            if (std::isdigit(c)) {
                i++;
            } else if (c == '.' && !has_dot) {
                has_dot = true;
                i++;
            } else {
                break;
            }
        }
        
        if (i == num_start || i == input.size()) return std::nullopt;
        
        double numeric_value;
        try {
            numeric_value = std::stod(std::string(input.substr(num_start, i - num_start)));
        } catch (...) {
            return std::nullopt;
        }
        
        // Parse unit part
        size_t unit_start = i;
        while (i < input.size() && !std::isspace(input[i])) i++;
        
        std::string_view unit = input.substr(unit_start, i - unit_start);
        
        auto ms = parse_unit(numeric_value, unit);
        if (!ms) return std::nullopt;
        
        // Skip trailing whitespace
        while (i < input.size() && std::isspace(input[i])) i++;
        
        return ms;  // Return parsed duration
    }
    
    static constexpr value_type default_() {
        using namespace std::chrono_literals;
        return 30s;  // Default to 30 seconds
    }

private:
    static std::optional<value_type> parse_unit(double value, std::string_view unit) noexcept {
        using namespace std::chrono_literals;
        
        if (unit.empty()) return std::nullopt;
        
        // Check for milliseconds first (must be exact match)
        if (unit == "ms" || unit == "msec" || unit == "milliseconds") {
            return static_cast<value_type>(static_cast<int64_t>(value));
        }
        
        // Seconds
        if (unit.substr(0, 1) == "s" && (unit.size() == 1 || 
            unit == "sec" || unit == "secs" || unit == "second" || unit == "seconds")) {
            return static_cast<value_type>(static_cast<int64_t>(value * 1000));
        }
        
        // Minutes
        if (unit.substr(0, 1) == "m" && (unit.size() == 1 ||
            unit == "min" || unit == "mins" || unit == "minute" || unit == "minutes")) {
            return static_cast<value_type>(static_cast<int64_t>(value * 60000));
        }
        
        // Hours
        if (unit.substr(0, 1) == "h" && (unit.size() == 1 ||
            unit == "hr" || unit == "hrs" || unit == "hour" || unit == "hours")) {
            return static_cast<value_type>(static_cast<int64_t>(value * 3600000));
        }
        
        // Days
        if (unit.substr(0, 1) == "d" && (unit.size() == 1 ||
            unit == "day" || unit == "days")) {
            return static_cast<value_type>(static_cast<int64_t>(value * 86400000));
        }
        
        return std::nullopt;
    }
};

// ============================================================================
// ByteSizeParser — Parse byte size strings to uint64_t bytes
//
// Supported formats (SI units):
//   - "1K" or "1KB" -> 1000 bytes
//   - "2M" or "2MB" -> 2000000 bytes
//   - "1G" or "1GB" -> 1000000000 bytes
//   - "1T" or "1TB" -> 1000000000000 bytes
//
// Also supports binary units (IEC):
//   - "1KiB" -> 1024 bytes
//   - "1MiB" -> 1048576 bytes
//   - etc.
// ============================================================================

struct ByteSizeParser {
    using value_type = uint64_t;
    
    static std::optional<value_type> parse(std::string_view input) noexcept {
        if (input.empty()) return std::nullopt;
        
        size_t i = 0;
        
        // Skip leading whitespace
        while (i < input.size() && std::isspace(input[i])) i++;
        
        // Parse numeric part
        size_t num_start = i;
        bool has_dot = false;
        while (i < input.size()) {
            char c = input[i];
            if (std::isdigit(c)) {
                i++;
            } else if (c == '.' && !has_dot) {
                has_dot = true;
                i++;
            } else {
                break;
            }
        }
        
        if (i == num_start) return std::nullopt;
        
        double numeric_value;
        try {
            numeric_value = std::stod(std::string(input.substr(num_start, i - num_start)));
        } catch (...) {
            return std::nullopt;
        }
        
        // Parse unit part
        size_t unit_start = i;
        while (i < input.size() && !std::isspace(input[i])) i++;
        
        std::string_view unit = input.substr(unit_start, i - unit_start);
        
        auto bytes = parse_unit(numeric_value, unit);
        if (!bytes) return std::nullopt;
        
        // Skip trailing whitespace
        while (i < input.size() && std::isspace(input[i])) i++;
        
        return *bytes;
    }
    
    static constexpr value_type default_() {
        return 0;  // No limit
    }

private:
    static std::optional<value_type> parse_unit(double value, std::string_view unit) noexcept {
        // SI units (base 1000)
        if (unit == "K" || unit == "KB") {
            return static_cast<value_type>(value * 1000);
        }
        if (unit == "M" || unit == "MB") {
            return static_cast<value_type>(value * 1000000);
        }
        if (unit == "G" || unit == "GB") {
            return static_cast<value_type>(value * 1000000000);
        }
        if (unit == "T" || unit == "TB") {
            return static_cast<value_type>(value * 1000000000000);
        }
        
        // Binary units (base 1024)
        if (unit == "KiB") {
            return static_cast<value_type>(value * 1024);
        }
        if (unit == "MiB") {
            return static_cast<value_type>(value * 1048576);
        }
        if (unit == "GiB") {
            return static_cast<value_type>(value * 1073741824);
        }
        if (unit == "TiB") {
            return static_cast<value_type>(value * 1099511627776ULL);
        }
        
        // Plain number means bytes
        if (unit.empty()) {
            return static_cast<value_type>(value);
        }
        
        return std::nullopt;
    }
};

// ============================================================================
// PathParser — Parse filesystem paths from command line
//
// Key behaviors:
//   - Preserves leading dashes in paths (e.g., "-filename" is valid)
//   - No glob expansion (shell expands globs before passing to Rebuntu)
//   - Handles spaces via quoting: "path with spaces"
//   - Supports both relative and absolute paths
// ============================================================================

struct PathParser {
    using value_type = std::filesystem::path;
    
    static std::optional<value_type> parse(std::string_view input) noexcept {
        if (input.empty()) return std::nullopt;
        
        // Skip leading/trailing whitespace for the final path
        size_t start = 0;
        while (start < input.size() && std::isspace(input[start])) start++;
        
        size_t end = input.size();
        while (end > start && std::isspace(input[end - 1])) end--;
        
        if (start >= end) return std::nullopt;
        
        try {
            return value_type{std::string(input.substr(start, end - start))};
        } catch (...) {
            return std::nullopt;
        }
    }
    
    static value_type default_() {
        return std::filesystem::current_path();
    }
};

// ============================================================================
// IdentifierParser — Parse valid identifiers
//
// Valid identifier rules:
//   - Must start with letter or underscore
//   - Can contain letters, digits, underscores, hyphens
//   - No spaces allowed
// ============================================================================

struct IdentifierParser {
    using value_type = std::string;
    
    static std::optional<value_type> parse(std::string_view input) noexcept {
        if (input.empty()) return std::nullopt;
        
        size_t i = 0;
        
        // Skip leading whitespace
        while (i < input.size() && std::isspace(input[i])) i++;
        
        if (i >= input.size()) return std::nullopt;
        
        // Check first character: must be letter or underscore
        char c = input[i];
        if (!std::isalpha(c) && c != '_') {
            return std::nullopt;
        }
        
        size_t start = i++;
        
        // Rest can be letters, digits, underscores, hyphens
        while (i < input.size()) {
            c = input[i];
            if (std::isalnum(c) || c == '_' || c == '-') {
                i++;
            } else {
                break;
            }
        }
        
        return value_type{input.substr(start, i - start)};
    }
    
    static value_type default_() {
        return "";
    }
};

// ============================================================================
// EnumParser — Parse string to enum value
//
// Usage:
//   struct MyEnum { A, B, C; };
//   EnumParser<MyEnum> parser = {{{"A", MyEnum::A}, {"B", MyEnum::B}}};
// ============================================================================

template<typename T>
struct EnumParser {
    using value_type = T;
    
    struct Mapping {
        std::string_view str;
        T value;
    };
    
private:
    std::vector<Mapping> mappings_;
    
public:
    explicit EnumParser(std::initializer_list<Mapping> mappings) : mappings_(mappings) {}
    
    std::optional<T> parse(std::string_view input) const noexcept {
        if (input.empty()) return std::nullopt;
        
        // Skip leading/trailing whitespace
        size_t start = 0;
        while (start < input.size() && std::isspace(input[start])) start++;
        
        size_t end = input.size();
        while (end > start && std::isspace(input[end - 1])) end--;
        
        if (start >= end) return std::nullopt;
        
        std::string_view trimmed = input.substr(start, end - start);
        
        for (const auto& mapping : mappings_) {
            if (mapping.str == trimmed) {
                return mapping.value;
            }
        }
        
        return std::nullopt;
    }
    
    static T default_() {
        return T{};
    }
};

// ============================================================================
// BooleanParser — Parse boolean values
//
// Accepts:
//   - true, True, TRUE -> true
//   - false, False, FALSE -> false
//   - yes, Yes, YES -> true
//   - no, No, NO -> false
//   - 1, 0 -> true/false
// ============================================================================

struct BooleanParser {
    using value_type = bool;
    
    static std::optional<value_type> parse(std::string_view input) noexcept {
        if (input.empty()) return std::nullopt;
        
        // Skip leading/trailing whitespace
        size_t start = 0;
        while (start < input.size() && std::isspace(input[start])) start++;
        
        size_t end = input.size();
        while (end > start && std::isspace(input[end - 1])) end--;
        
        if (start >= end) return std::nullopt;
        
        std::string_view trimmed = input.substr(start, end - start);
        
        // True values
        if (trimmed == "true" || trimmed == "True" || trimmed == "TRUE" ||
            trimmed == "yes" || trimmed == "Yes" || trimmed == "YES" ||
            trimmed == "1") {
            return true;
        }
        
        // False values
        if (trimmed == "false" || trimmed == "False" || trimmed == "FALSE" ||
            trimmed == "no" || trimmed == "No" || trimmed == "NO" ||
            trimmed == "0" || trimmed == "") {
            return false;
        }
        
        return std::nullopt;
    }
    
    static constexpr value_type default_() {
        return false;
    }
};

// ============================================================================
// ListParser — Parse comma or space-separated list
//
// Quoted strings can contain the separator character:
//   - "a,b,c" -> ["a", "b", "c"]
//   - "a, b, c" -> ["a", "b", "c"] (spaces after commas ignored)
//   - "'one two',three" -> ["one two", "three"] (quoted items preserved)
// ============================================================================

struct ListParser {
    using value_type = std::vector<std::string>;
    
    static std::optional<value_type> parse(std::string_view input) noexcept {
        if (input.empty()) return value_type{};
        
        value_type result;
        std::string current;
        
        size_t i = 0;
        
        // Skip leading whitespace
        while (i < input.size() && std::isspace(input[i])) i++;
        
        bool in_quote = false;
        char quote_char = '\0';
        
        while (i < input.size()) {
            char c = input[i];
            
            if (!in_quote) {
                if (c == '"' || c == '\'') {
                    in_quote = true;
                    quote_char = c;
                } else if (c == ',' || std::isspace(c)) {
                    // Separator found - end of current item
                    if (!current.empty()) {
                        result.push_back(current);
                        current.clear();
                    }
                } else {
                    current += c;
                }
            } else {
                if (c == quote_char) {
                    in_quote = false;
                    quote_char = '\0';
                } else {
                    current += c;
                }
            }
            
            i++;
        }
        
        // Add final item
        if (!current.empty()) {
            result.push_back(current);
        }
        
        return result;
    }
    
    static value_type default_() {
        return {};
    }
};

// ============================================================================
// ValueConverter — Unified API for type conversion
// ============================================================================

template<typename T>
struct ValueConverter;

template<>
struct ValueConverter<std::chrono::milliseconds> {
    using Parser = DurationParser;
    static std::optional<std::chrono::milliseconds> parse(std::string_view s) {
        return Parser::parse(s);
    }
};

template<>
struct ValueConverter<uint64_t> {
    using Parser = ByteSizeParser;
    static std::optional<uint64_t> parse(std::string_view s) {
        return Parser::parse(s);
    }
};

template<>
struct ValueConverter<std::filesystem::path> {
    using Parser = PathParser;
    static std::optional<std::filesystem::path> parse(std::string_view s) {
        return Parser::parse(s);
    }
};

template<>
struct ValueConverter<std::string> {
    using Parser = IdentifierParser;
    static std::optional<std::string> parse(std::string_view s) {
        return Parser::parse(s);
    }
};

template<>
struct ValueConverter<bool> {
    using Parser = BooleanParser;
    static std::optional<bool> parse(std::string_view s) {
        return Parser::parse(s);
    }
};

template<>
struct ValueConverter<std::vector<std::string>> {
    using Parser = ListParser;
    static std::optional<std::vector<std::string>> parse(std::string_view s) {
        return Parser::parse(s);
    }
};

}  // namespace rebuntu::shell::values