// rebuntu::environment::secrets — Secret Reference Model (Phase 2.11)
//
// This establishes Rebuntu's canonical secret reference model:
//
//   - Secret references are OPAQUE identifiers to native credential storage
//   - Never contains actual secret material
//   - Supports multiple providers: systemd credentials, keyring, env
//   - Provides redaction at log/serialization boundaries
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/secrets.hpp
//
// Phase 2.11 extends config_storage (atomic writes) and scope (user/system/session):
// - Defines SecretRef type for opaque secret identification
// - Provides provider abstraction for native credential storage
// - Implements redaction framework for safe serialization

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <map>
#include <memory>
#include <functional>

#include <system/environment/scope.hpp>
#include <system/core/contracts.hpp>

namespace rebuntu::environment::secrets {

// ============================================================================
// SecretProvider - Native credential storage mechanisms
// ============================================================================

enum class SecretProvider {
    kSystemd,      // systemd credentials (/run/credentials/)
    kKeyring,      // User keyring (Secret Service D-Bus / libsecret)
    kEnv,          // Environment variable (for testing/debugging only!)
};

inline std::string_view to_string(SecretProvider p) {
    switch (p) {
        case SecretProvider::kSystemd: return "systemd";
        case SecretProvider::kKeyring: return "keyring";
        case SecretProvider::kEnv:     return "env";
    }
    return "unknown";
}

// ============================================================================
// SecretRef - Opaque reference to a secret (NEVER contains actual value)
// ============================================================================

struct SecretRef {
    // Which provider stores this secret?
    SecretProvider provider = SecretProvider::kKeyring;
    
    // Scope where the secret is accessible
    rebuntu::environment::scope::ExecutionScope scope = rebuntu::environment::scope::ExecutionScope::kUser;
    
    // Key/identifier within the provider's namespace
    std::string key;
    
    // Optional human-readable description (for logs/diagnostic use)
    std::optional<std::string> description;
    
    // Redaction policy for this reference
    bool should_redact = true;
    
    // Equality comparison for use in containers
    bool operator==(const SecretRef& other) const {
        return provider == other.provider &&
               scope == other.scope &&
               key == other.key &&
               description == other.description &&
               should_redact == other.should_redact;
    }
    
    // Less-than for std::map ordering
    bool operator<(const SecretRef& other) const {
        if (provider != other.provider) return provider < other.provider;
        if (scope != other.scope) return scope < other.scope;
        return key < other.key;
    }
};

// Hash support for std::unordered_map
struct SecretRefHash {
    size_t operator()(const SecretRef& ref) const {
        size_t h1 = std::hash<int>{}(static_cast<int>(ref.provider));
        size_t h2 = std::hash<int>{}(static_cast<int>(ref.scope));
        size_t h3 = std::hash<std::string>{}(ref.key);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

// ============================================================================
// SecretResolveResult - Result of resolving a secret reference
// ============================================================================

struct SecretResolveResult {
    rebuntu::core::SemanticStatus status = rebuntu::core::SemanticStatus::kUnknown;
    
    // The resolved secret value (if successful)
    // Never cached - always fresh from native storage
    std::optional<std::string> value;
    
    // Provider that provided the value (for audit trail)
    std::optional<SecretProvider> source_provider;
    
    // Error details if resolution failed
    std::optional<std::string> error_message;
    std::optional<std::string> provider_error;  // Raw provider error if available
    
    bool is_success() const { return status == rebuntu::core::SemanticStatus::kSuccess; }
    bool is_failure() const { return status == rebuntu::core::SemanticStatus::kFailure; }
    bool is_unknown() const { return status == rebuntu::core::SemanticStatus::kUnknown; }
};

// ============================================================================
// SecretStore - Abstract interface for secret storage providers
// ============================================================================

class SecretStore {
public:
    virtual ~SecretStore() = default;
    
    // Get the provider this store implements
    virtual SecretProvider provider() const = 0;
    
    // Resolve a secret reference to its value (if available)
    virtual SecretResolveResult resolve(const SecretRef& ref) = 0;
    
    // Check if a provider is available (e.g., systemd credentials dir exists)
    virtual bool is_available() const = 0;
};

// ============================================================================
// Provider Registry - Register and lookup secret stores
// ============================================================================

class SecretStoreRegistry {
public:
    static SecretStoreRegistry& instance();
    
    // Register a secret store provider
    void register_store(std::unique_ptr<SecretStore> store);
    
    // Get a store by provider type (returns null if not registered)
    SecretStore* get_store(SecretProvider provider) const;
    
    // Resolve a secret reference using the appropriate provider
    SecretResolveResult resolve(const SecretRef& ref);
    
    // Get all available providers for a scope
    std::vector<SecretProvider> get_available_providers(
        rebuntu::environment::scope::ExecutionScope scope) const;

private:
    SecretStoreRegistry() = default;
    
    // Map from provider type to store instance
    std::map<SecretProvider, std::unique_ptr<SecretStore>> stores_;
};

// ============================================================================
// Redaction Framework - Never expose secret values in logs/diffs
// ============================================================================

struct RedactionPolicy {
    bool is_secret = false;
    std::string redacted_value = "[REDACTED]";
    
    static RedactionPolicy secret() { return {true, "[REDACTED]"}; }
    static RedactionPolicy normal() { return {false, ""}; }
};

// Get a redacted view of config values (secrets replaced with placeholder)
std::map<std::string, std::string> get_redacted_values(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretRef>& secret_refs);

// Format values for output, applying redaction to secrets
std::string format_config_for_display(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretRef>& secret_refs = {});

// Get a string representation of a SecretRef that's safe for logging
std::string to_log_string(const SecretRef& ref);

// ============================================================================
// Native Provider Detection - Which secret stores are available?
// ============================================================================

// Check if systemd credentials directory exists and is accessible
bool has_systemd_credentials();

// Check if user session keyring is available
bool has_user_keyring(uid_t uid = 0);

// Get the default provider for a scope
SecretProvider get_default_provider(rebuntu::environment::scope::ExecutionScope scope);

// ============================================================================
// Secret Reference Factory - Create references for common patterns
// ============================================================================

// Create a reference to a systemd credential
SecretRef create_systemd_credential(
    std::string key,
    rebuntu::environment::scope::ExecutionScope scope = 
        rebuntu::environment::scope::ExecutionScope::kSystem);

// Create a reference to a user keyring entry
SecretRef create_keyring_entry(
    std::string key,
    uid_t uid = 0,
    rebuntu::environment::scope::ExecutionScope scope = 
        rebuntu::environment::scope::ExecutionScope::kUser);

// Create a reference to an environment variable (testing only!)
SecretRef create_env_reference(
    std::string env_var_name,
    rebuntu::environment::scope::ExecutionScope scope = 
        rebuntu::environment::scope::ExecutionScope::kSession);

}  // namespace rebuntu::environment::secrets

// Hash specialization for std::unordered_map support
namespace std {
template<>
struct hash<rebuntu::environment::secrets::SecretRef> {
    size_t operator()(const rebuntu::environment::secrets::SecretRef& ref) const {
        return rebuntu::environment::secrets::SecretRefHash{}(ref);
    }
};
}