// Rebuntu Secrets Module Tests (Phase 2.11)
// ===========================================
// Testing Secret Reference Model implementation

#include "system/environment/secrets.hpp"
#include <cassert>
#include <iostream>
#include <cstdlib>

using namespace rebuntu::environment::secrets;

void test_secret_ref_creation() {
    // Test creating a secret reference
    SecretRef ref;
    
    assert(ref.provider == rebuntu::environment::secrets::SecretProvider::kKeyring);
    assert(ref.scope == rebuntu::environment::scope::ExecutionScope::kUser);
    assert(ref.key.empty());
    assert(!ref.description.has_value());
    assert(ref.should_redact);
    
    std::cout << "test_secret_ref_creation: PASSED" << std::endl;
}

void test_secret_ref_equality() {
    // Test equality operator
    SecretRef ref1;
    ref1.key = "mysecret";
    
    SecretRef ref2;
    ref2.key = "mysecret";
    
    assert(ref1 == ref2);
    
    std::cout << "test_secret_ref_equality: PASSED" << std::endl;
}

void test_secret_provider_to_string() {
    using namespace rebuntu::environment::secrets;
    
    assert(to_string(SecretProvider::kSystemd) == "systemd");
    assert(to_string(SecretProvider::kKeyring) == "keyring");
    assert(to_string(SecretProvider::kEnv) == "env");
    
    std::cout << "test_secret_provider_to_string: PASSED" << std::endl;
}

void test_create_systemd_credential() {
    auto ref = create_systemd_credential("PASSWORD", 
        rebuntu::environment::scope::ExecutionScope::kSystem);
    
    assert(ref.provider == rebuntu::environment::secrets::SecretProvider::kSystemd);
    assert(ref.scope == rebuntu::environment::scope::ExecutionScope::kSystem);
    assert(ref.key == "PASSWORD");
    assert(ref.description.has_value());
    assert(ref.should_redact);
    
    std::cout << "test_create_systemd_credential: PASSED" << std::endl;
}

void test_create_keyring_entry() {
    auto ref = create_keyring_entry("API_TOKEN");
    
    assert(ref.provider == rebuntu::environment::secrets::SecretProvider::kKeyring);
    // User scope because we're not root
    assert(ref.should_redact);
    
    std::cout << "test_create_keyring_entry: PASSED" << std::endl;
}

void test_create_env_reference() {
    auto ref = create_env_reference("DB_PASSWORD");
    
    assert(ref.provider == rebuntu::environment::secrets::SecretProvider::kEnv);
    assert(ref.key == "DB_PASSWORD");
    assert(ref.should_redact);
    
    std::cout << "test_create_env_reference: PASSED" << std::endl;
}

void test_has_systemd_credentials() {
    // Check that the function exists and returns a bool
    bool available = rebuntu::environment::secrets::has_systemd_credentials();
    (void)available;  // Suppress unused warning
    
    std::cout << "test_has_systemd_credentials: PASSED" << std::endl;
}

void test_get_default_provider() {
    auto provider = get_default_provider(
        rebuntu::environment::scope::ExecutionScope::kSystem);
    
    // Should be kEnv for testing (since we don't have native credential storage)
    assert(provider == rebuntu::environment::secrets::SecretProvider::kEnv ||
           provider == rebuntu::environment::secrets::SecretProvider::kSystemd);
    
    std::cout << "test_get_default_provider: PASSED" << std::endl;
}

void test_secret_store_registry() {
    auto& registry = SecretStoreRegistry::instance();
    
    // Should be able to get the environment store
    auto store = registry.get_store(SecretProvider::kEnv);
    assert(store != nullptr);
    assert(store->provider() == rebuntu::environment::secrets::SecretProvider::kEnv);
    
    std::cout << "test_secret_store_registry: PASSED" << std::endl;
}

void test_env_secret_resolution() {
    // Set an environment variable
    setenv("REBUNTU_TEST_SECRET", "secret_value_123", 1);
    
    SecretRef ref;
    ref.provider = SecretProvider::kEnv;
    ref.scope = rebuntu::environment::scope::ExecutionScope::kSession;
    ref.key = "REBUNTU_TEST_SECRET";
    
    auto result = SecretStoreRegistry::instance().resolve(ref);
    
    // Should succeed and return the value
    assert(result.is_success());
    assert(result.value.has_value());
    assert(*result.value == "secret_value_123");
    assert(result.source_provider.has_value());
    assert(*result.source_provider == rebuntu::environment::secrets::SecretProvider::kEnv);
    
    // Cleanup
    unsetenv("REBUNTU_TEST_SECRET");
    
    std::cout << "test_env_secret_resolution: PASSED" << std::endl;
}

void test_redaction_framework() {
    std::map<std::string, std::string> values = {
        {"username", "admin"},
        {"password", "secret123"},
        {"api_key", "key456"},
        {"normal_value", "hello"}
    };
    
    // Create secret refs
    SecretRef password_ref;
    password_ref.key = "password";
    password_ref.should_redact = true;
    
    SecretRef api_ref;
    api_ref.key = "api_key";
    api_ref.should_redact = true;
    
    std::vector<SecretRef> secret_refs = {password_ref, api_ref};
    
    // Get redacted values
    auto redacted = get_redacted_values(values, secret_refs);
    
    assert(redacted.at("username") == "admin");
    assert(redacted.at("password") == "[REDACTED]");
    assert(redacted.at("api_key") == "[REDACTED]");
    assert(redacted.at("normal_value") == "hello");
    
    // Format for display
    std::string formatted = format_config_for_display(values, secret_refs);
    
    // Check that redacted values appear in output
    assert(formatted.find("[REDACTED]") != std::string::npos);
    assert(formatted.find("secret123") == std::string::npos);  // Actual value should not be present
    
    std::cout << "test_redaction_framework: PASSED" << std::endl;
}

void test_to_log_string() {
    SecretRef ref;
    ref.provider = SecretProvider::kKeyring;
    ref.scope = rebuntu::environment::scope::ExecutionScope::kUser;
    ref.key = "my_secret";
    
    std::string log_str = to_log_string(ref);
    
    // Should not contain the secret value (it's just a reference)
    assert(log_str.find("keyring") != std::string::npos);
    assert(log_str.find("user") != std::string::npos);
    assert(log_str.find("my_secret") != std::string::npos);
    
    std::cout << "test_to_log_string: PASSED" << std::endl;
}

void test_empty_key_resolution() {
    // Test that empty keys are handled properly
    SecretRef ref;
    ref.provider = SecretProvider::kEnv;
    ref.key = "";
    
    auto result = SecretStoreRegistry::instance().resolve(ref);
    
    // Should fail with empty key
    assert(result.is_failure() || result.is_unknown());
    
    std::cout << "test_empty_key_resolution: PASSED" << std::endl;
}

void test_nonexistent_env_variable() {
    // Try to resolve a nonexistent environment variable
    SecretRef ref;
    ref.provider = SecretProvider::kEnv;
    ref.key = "NONEXISTENT_REBUNTU_TEST_VAR_12345";
    
    auto result = SecretStoreRegistry::instance().resolve(ref);
    
    // Should return unknown (not found)
    assert(result.is_unknown());
    
    std::cout << "test_nonexistent_env_variable: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Rebuntu Secrets Module Tests (Phase 2.11)" << std::endl;
    std::cout << "===================================================" << std::endl;
    
    // Basic type tests
    test_secret_ref_creation();
    test_secret_ref_equality();
    test_secret_provider_to_string();
    
    // Factory function tests
    test_create_systemd_credential();
    test_create_keyring_entry();
    test_create_env_reference();
    
    // Provider detection tests
    test_has_systemd_credentials();
    test_get_default_provider();
    
    // Registry tests
    test_secret_store_registry();
    
    // Secret resolution tests (using Env store)
    test_env_secret_resolution();
    test_empty_key_resolution();
    test_nonexistent_env_variable();
    
    // Redaction tests
    test_redaction_framework();
    test_to_log_string();
    
    std::cout << "===================================================" << std::endl;
    std::cout << "All secrets module tests PASSED" << std::endl;
    
    return 0;
}