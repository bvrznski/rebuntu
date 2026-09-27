// rebuntu - Phase 6.6 Value Parsers Unit Tests
//
// Test matrix for typed value parsers:
//   - DurationParser: duration strings to std::chrono::milliseconds
//   - ByteSizeParser: byte size strings to uint64_t bytes
//   - PathParser: filesystem paths
//   - IdentifierParser: valid identifiers
//   - BooleanParser: boolean values
//   - ListParser: comma/space-separated lists

#include "../../../src/system/shell/values.hpp"
#include <iostream>
#include <sstream>

using namespace rebuntu::shell::values;

// ============================================================================
// DurationParser Tests
// ============================================================================

void test_duration_valid_seconds() {
    std::cout << "[TEST] DurationParser valid seconds...";
    
    auto result = DurationParser::parse("30s");
    if (!result || result->count() != 30000) {
        std::cerr << " [FAIL - 30s should be 30000ms]\n";
        return;
    }
    
    result = DurationParser::parse("5sec");
    if (!result || result->count() != 5000) {
        std::cerr << " [FAIL - 5sec should be 5000ms]\n";
        return;
    }
    
    result = DurationParser::parse("10seconds");
    if (!result || result->count() != 10000) {
        std::cerr << " [FAIL - 10seconds should be 10000ms]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_duration_valid_minutes() {
    std::cout << "[TEST] DurationParser valid minutes...";
    
    auto result = DurationParser::parse("5m");
    if (!result || result->count() != 300000) {
        std::cerr << " [FAIL - 5m should be 300000ms]\n";
        return;
    }
    
    result = DurationParser::parse("2min");
    if (!result || result->count() != 120000) {
        std::cerr << " [FAIL - 2min should be 120000ms]\n";
        return;
    }
    
    result = DurationParser::parse("1minutes");
    if (!result || result->count() != 60000) {
        std::cerr << " [FAIL - 1minutes should be 60000ms]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_duration_valid_hours() {
    std::cout << "[TEST] DurationParser valid hours...";
    
    auto result = DurationParser::parse("2h");
    if (!result || result->count() != 7200000) {
        std::cerr << " [FAIL - 2h should be 7200000ms]\n";
        return;
    }
    
    result = DurationParser::parse("1hour");
    if (!result || result->count() != 3600000) {
        std::cerr << " [FAIL - 1hour should be 3600000ms]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_duration_valid_milliseconds() {
    std::cout << "[TEST] DurationParser valid milliseconds...";
    
    auto result = DurationParser::parse("150ms");
    if (!result || result->count() != 150) {
        std::cerr << " [FAIL - 150ms should be 150ms]\n";
        return;
    }
    
    result = DurationParser::parse("100msec");
    if (!result || result->count() != 100) {
        std::cerr << " [FAIL - 100msec should be 100ms]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_duration_decimal_values() {
    std::cout << "[TEST] DurationParser decimal values...";
    
    auto result = DurationParser::parse("1.5s");
    if (!result || result->count() != 1500) {
        std::cerr << " [FAIL - 1.5s should be 1500ms]\n";
        return;
    }
    
    result = DurationParser::parse("2.5m");
    if (!result || result->count() != 150000) {
        std::cerr << " [FAIL - 2.5m should be 150000ms]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_duration_invalid_formats() {
    std::cout << "[TEST] DurationParser invalid formats...";
    
    auto result = DurationParser::parse("");
    if (result) {
        std::cerr << " [FAIL - empty string should fail]\n";
        return;
    }
    
    result = DurationParser::parse("invalid");
    if (result) {
        std::cerr << " [FAIL - 'invalid' should fail]\n";
        return;
    }
    
    result = DurationParser::parse("10x");
    if (result) {
        std::cerr << " [FAIL - '10x' invalid unit should fail]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_duration_trailing_whitespace() {
    std::cout << "[TEST] DurationParser trailing whitespace...";
    
    auto result = DurationParser::parse("30s  ");
    if (!result || result->count() != 30000) {
        std::cerr << " [FAIL - should handle trailing whitespace]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

// ============================================================================
// ByteSizeParser Tests
// ============================================================================

void test_bytesize_valid_si_units() {
    std::cout << "[TEST] ByteSizeParser valid SI units...";
    
    auto result = ByteSizeParser::parse("1K");
    if (!result || *result != 1000) {
        std::cerr << " [FAIL - 1K should be 1000]\n";
        return;
    }
    
    result = ByteSizeParser::parse("2MB");
    if (!result || *result != 2000000) {
        std::cerr << " [FAIL - 2MB should be 2000000]\n";
        return;
    }
    
    result = ByteSizeParser::parse("1GB");
    if (!result || *result != 1000000000ULL) {
        std::cerr << " [FAIL - 1GB should be 1000000000]\n";
        return;
    }
    
    result = ByteSizeParser::parse("1T");
    if (!result || *result != 1000000000000ULL) {
        std::cerr << " [FAIL - 1T should be 1000000000000]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_bytesize_valid_binary_units() {
    std::cout << "[TEST] ByteSizeParser valid binary units...";
    
    auto result = ByteSizeParser::parse("1KiB");
    if (!result || *result != 1024) {
        std::cerr << " [FAIL - 1KiB should be 1024]\n";
        return;
    }
    
    result = ByteSizeParser::parse("1MiB");
    if (!result || *result != 1048576) {
        std::cerr << " [FAIL - 1MiB should be 1048576]\n";
        return;
    }
    
    result = ByteSizeParser::parse("1GiB");
    if (!result || *result != 1073741824ULL) {
        std::cerr << " [FAIL - 1GiB should be 1073741824]\n";
        return;
    }
    
    result = ByteSizeParser::parse("1TiB");
    if (!result || *result != 1099511627776ULL) {
        std::cerr << " [FAIL - 1TiB should be 1099511627776]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_bytesize_decimal_values() {
    std::cout << "[TEST] ByteSizeParser decimal values...";
    
    auto result = ByteSizeParser::parse("1.5K");
    if (!result || *result != 1500) {
        std::cerr << " [FAIL - 1.5K should be 1500]\n";
        return;
    }
    
    result = ByteSizeParser::parse("2.5MB");
    if (!result || *result != 2500000) {
        std::cerr << " [FAIL - 2.5MB should be 2500000]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_bytesize_plain_number() {
    std::cout << "[TEST] ByteSizeParser plain number (bytes)...";
    
    auto result = ByteSizeParser::parse("12345");
    if (!result || *result != 12345) {
        std::cerr << " [FAIL - plain number should be bytes]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_bytesize_invalid() {
    std::cout << "[TEST] ByteSizeParser invalid formats...";
    
    auto result = ByteSizeParser::parse("");
    if (result) {
        std::cerr << " [FAIL - empty should fail]\n";
        return;
    }
    
    result = ByteSizeParser::parse("invalid");
    if (result) {
        std::cerr << " [FAIL - 'invalid' should fail]\n";
        return;
    }
    
    result = ByteSizeParser::parse("10x");
    if (result) {
        std::cerr << " [FAIL - '10x' invalid unit should fail]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

// ============================================================================
// PathParser Tests
// ============================================================================

void test_path_simple() {
    std::cout << "[TEST] PathParser simple paths...";
    
    auto result = PathParser::parse("/usr/bin/rebuntu");
    if (!result) {
        std::cerr << " [FAIL - /usr/bin/rebuntu should parse]\n";
        return;
    }
    
    if (result->string() != "/usr/bin/rebuntu") {
        std::cerr << " [FAIL - path mismatch]\n";
        return;
    }
    
    result = PathParser::parse("relative/path");
    if (!result || result->string() != "relative/path") {
        std::cerr << " [FAIL - relative path should parse]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_path_with_spaces() {
    std::cout << "[TEST] PathParser paths with spaces...";
    
    // Paths with spaces must be quoted by the shell before reaching Rebuntu
    auto result = PathParser::parse("/path/with spaces/file.txt");
    if (!result || result->string() != "/path/with spaces/file.txt") {
        std::cerr << " [FAIL - path with spaces should parse]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_path_leading_dash() {
    std::cout << "[TEST] PathParser paths starting with dash...";
    
    auto result = PathParser::parse("-filename");
    if (!result || result->string() != "-filename") {
        std::cerr << " [FAIL - leading dash should be preserved]\n";
        return;
    }
    
    result = PathParser::parse("--options");
    if (!result || result->string() != "--options") {
        std::cerr << " [FAIL - double dash should be preserved]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_path_empty() {
    std::cout << "[TEST] PathParser empty input...";
    
    auto result = PathParser::parse("");
    if (result) {
        std::cerr << " [FAIL - empty should fail]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

// ============================================================================
// IdentifierParser Tests
// ============================================================================

void test_identifier_valid() {
    std::cout << "[TEST] IdentifierParser valid identifiers...";
    
    auto result = IdentifierParser::parse("test");
    if (!result || *result != "test") {
        std::cerr << " [FAIL - 'test' should parse]\n";
        return;
    }
    
    result = IdentifierParser::parse("_private");
    if (!result || *result != "_private") {
        std::cerr << " [FAIL - '_private' should parse]\n";
        return;
    }
    
    result = IdentifierParser::parse("my-var_123");
    if (!result || *result != "my-var_123") {
        std::cerr << " [FAIL - 'my-var_123' should parse]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_identifier_invalid() {
    std::cout << "[TEST] IdentifierParser invalid identifiers...";
    
    auto result = IdentifierParser::parse("123abc");  // starts with digit
    if (result) {
        std::cerr << " [FAIL - '123abc' should fail (starts with digit)]\n";
        return;
    }
    
    result = IdentifierParser::parse("-invalid");  // starts with dash
    if (result) {
        std::cerr << " [FAIL - '-invalid' should fail]\n";
        return;
    }
    
    result = IdentifierParser::parse("has space");
    if (result && *result == "has space") {
        std::cerr << " [FAIL - 'has space' should fail (contains space)]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

// ============================================================================
// BooleanParser Tests
// ============================================================================

void test_boolean_true_values() {
    std::cout << "[TEST] BooleanParser true values...";
    
    auto result = BooleanParser::parse("true");
    if (!result || !*result) {
        std::cerr << " [FAIL - 'true' should be true]\n";
        return;
    }
    
    result = BooleanParser::parse("True");
    if (!result || !*result) {
        std::cerr << " [FAIL - 'True' should be true]\n";
        return;
    }
    
    result = BooleanParser::parse("TRUE");
    if (!result || !*result) {
        std::cerr << " [FAIL - 'TRUE' should be true]\n";
        return;
    }
    
    result = BooleanParser::parse("yes");
    if (!result || !*result) {
        std::cerr << " [FAIL - 'yes' should be true]\n";
        return;
    }
    
    result = BooleanParser::parse("1");
    if (!result || !*result) {
        std::cerr << " [FAIL - '1' should be true]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_boolean_false_values() {
    std::cout << "[TEST] BooleanParser false values...";
    
    auto result = BooleanParser::parse("false");
    if (!result || *result) {
        std::cerr << " [FAIL - 'false' should be false]\n";
        return;
    }
    
    result = BooleanParser::parse("False");
    if (!result || *result) {
        std::cerr << " [FAIL - 'False' should be false]\n";
        return;
    }
    
    result = BooleanParser::parse("FALSE");
    if (!result || *result) {
        std::cerr << " [FAIL - 'FALSE' should be false]\n";
        return;
    }
    
    result = BooleanParser::parse("no");
    if (!result || *result) {
        std::cerr << " [FAIL - 'no' should be false]\n";
        return;
    }
    
    result = BooleanParser::parse("0");
    if (!result || *result) {
        std::cerr << " [FAIL - '0' should be false]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_boolean_invalid() {
    std::cout << "[TEST] BooleanParser invalid values...";
    
    auto result = BooleanParser::parse("");
    if (result) {
        std::cerr << " [FAIL - empty should fail]\n";
        return;
    }
    
    result = BooleanParser::parse("maybe");
    if (result) {
        std::cerr << " [FAIL - 'maybe' should fail]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

// ============================================================================
// ListParser Tests
// ============================================================================

void test_list_comma_separated() {
    std::cout << "[TEST] ListParser comma-separated...";
    
    auto result = ListParser::parse("a,b,c");
    if (!result || result->size() != 3 || (*result)[0] != "a" || (*result)[1] != "b" || (*result)[2] != "c") {
        std::cerr << " [FAIL - 'a,b,c' should parse to 3 items]\n";
        return;
    }
    
    result = ListParser::parse("one,two,three");
    if (!result || result->size() != 3) {
        std::cerr << " [FAIL - 'one,two,three' should parse]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_list_space_separated() {
    std::cout << "[TEST] ListParser space-separated...";
    
    auto result = ListParser::parse("a b c");
    if (!result || result->size() != 3) {
        std::cerr << " [FAIL - 'a b c' should parse to 3 items]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_list_quoted_items() {
    std::cout << "[TEST] ListParser quoted items...";
    
    auto result = ListParser::parse("\"one two\",three");
    if (!result || result->size() != 2 || (*result)[0] != "one two") {
        std::cerr << " [FAIL - quoted item should preserve spaces]\n";
        return;
    }
    
    result = ListParser::parse("'item with spaces',another");
    if (!result || result->size() != 2) {
        std::cerr << " [FAIL - single-quoted items should work]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_list_empty() {
    std::cout << "[TEST] ListParser empty input...";
    
    auto result = ListParser::parse("");
    if (!result || !result->empty()) {
        std::cerr << " [FAIL - empty should return empty vector]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main() {
    std::cout << "Phase 6.6 Value Parsers Unit Tests\n";
    std::cout << "===================================\n\n";
    
    // DurationParser tests
    test_duration_valid_seconds();
    test_duration_valid_minutes();
    test_duration_valid_hours();
    test_duration_valid_milliseconds();
    test_duration_decimal_values();
    test_duration_invalid_formats();
    test_duration_trailing_whitespace();
    
    std::cout << "\n";
    
    // ByteSizeParser tests
    test_bytesize_valid_si_units();
    test_bytesize_valid_binary_units();
    test_bytesize_decimal_values();
    test_bytesize_plain_number();
    test_bytesize_invalid();
    
    std::cout << "\n";
    
    // PathParser tests
    test_path_simple();
    test_path_with_spaces();
    test_path_leading_dash();
    test_path_empty();
    
    std::cout << "\n";
    
    // IdentifierParser tests
    test_identifier_valid();
    test_identifier_invalid();
    
    std::cout << "\n";
    
    // BooleanParser tests
    test_boolean_true_values();
    test_boolean_false_values();
    test_boolean_invalid();
    
    std::cout << "\n";
    
    // ListParser tests
    test_list_comma_separated();
    test_list_space_separated();
    test_list_quoted_items();
    test_list_empty();
    
    std::cout << "\n===================================\n";
    std::cout << "All value parser tests completed!\n";
    return 0;
}