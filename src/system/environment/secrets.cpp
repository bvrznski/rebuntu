// rebuntu::environment::secrets — Secret Reference Implementation (Phase 2.11)
#include "system/environment/secrets.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <cerrno>
#include <filesystem>

namespace rebuntu::environment::secrets {

// ============================================================================
// Native Provider Detection - Implementation
// ============================================================================

bool has_systemd_credentials() {
    // Check for systemd credential directory
    // System: /run/credentials/
    // User: $XDG_RUNTIME_DIR/credentials/
    
    struct stat st;
    
    // Try system path first
    if (stat("/run/credentials", &st) == 0 && S_ISDIR(st.st_mode)) {
        return true;
    }
    
    // Check user credential directory in XDG_RUNTIME_DIR
    const char* runtime_dir = std::getenv("XDG_RUNTIME_DIR");
    if (runtime_dir) {
        std::filesystem::path cred_path = std::filesystem::path(runtime_dir) / "credentials";
        if (stat(cred_path.string().c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
            return true;
        }
    }
    
    return false;
}

bool has_user_keyring(uid_t uid) {
    // For now, return true as a placeholder
    // Full implementation would check for Secret Service D-Bus availability
    // or libsecret availability
    
    if (uid == 0) {
        // Root doesn't have a user keyring
        return false;
    }
    
    // Check if we can access the D-Bus session bus
    const char* dbus_session = std::getenv("DBUS_SESSION_BUS_ADDRESS");
    if (!dbus_session || strlen(dbus_session) == 0) {
        return false;
    }
    
    return true;
}

SecretProvider get_default_provider(rebuntu::environment::scope::ExecutionScope scope) {
    switch (scope) {
        case rebuntu::environment::scope::ExecutionScope::kSystem:
            // System-wide: prefer systemd credentials
            if (has_systemd_credentials()) {
                return SecretProvider::kSystemd;
            }
            return SecretProvider::kEnv;  // Fallback for testing
        
        case rebuntu::environment::scope::ExecutionScope::kUser:
        case rebuntu::environment::scope::ExecutionScope::kSession:
            // User/session: prefer keyring, fall back to env
            if (has_user_keyring(getuid())) {
                return SecretProvider::kKeyring;
            }
            return SecretProvider::kEnv;  // Fallback for testing
        
        default:
            return SecretProvider::kEnv;  // Default fallback
    }
}

// ============================================================================
// Redaction Framework - Implementation
// ============================================================================

std::map<std::string, std::string> get_redacted_values(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretRef>& secret_refs) {
    
    std::map<std::string, std::string> result;
    
    // Build a set of keys that should be redacted
    std::set<std::string> redact_keys;
    for (const auto& ref : secret_refs) {
        if (ref.should_redact) {
            redact_keys.insert(ref.key);
        }
    }
    
    for (const auto& [key, value] : values) {
        result[key] = (redact_keys.count(key) > 0) ? "[REDACTED]" : value;
    }
    
    return result;
}

std::string format_config_for_display(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretRef>& secret_refs) {
    
    std::ostringstream ss;
    
    // Build a set of keys that should be redacted
    std::set<std::string> redact_keys;
    for (const auto& ref : secret_refs) {
        if (ref.should_redact) {
            redact_keys.insert(ref.key);
        }
    }
    
    for (const auto& [key, value] : values) {
        ss << key << " = ";
        if (redact_keys.count(key) > 0) {
            ss << "[REDACTED]";
        } else {
            ss << value;
        }
        ss << "\n";
    }
    
    return ss.str();
}

std::string to_log_string(const SecretRef& ref) {
    std::ostringstream ss;
    ss << "SecretRef{provider=" << to_string(ref.provider)
       << ", scope=" << rebuntu::environment::scope::to_string(ref.scope)
       << ", key=" << ref.key;
    
    if (ref.description.has_value()) {
        ss << ", description=\"" << ref.description.value() << "\"";
    }
    
    ss << "}";
    return ss.str();
}

// ============================================================================
// Secret Reference Factory - Implementation
// ============================================================================

SecretRef create_systemd_credential(
    std::string key,
    rebuntu::environment::scope::ExecutionScope scope) {
    
    SecretRef ref;
    ref.provider = SecretProvider::kSystemd;
    ref.scope = scope;
    ref.key = std::move(key);
    ref.description = "systemd credential";
    ref.should_redact = true;
    
    return ref;
}

SecretRef create_keyring_entry(
    std::string key,
    uid_t uid,
    rebuntu::environment::scope::ExecutionScope scope) {
    
    SecretRef ref;
    ref.provider = SecretProvider::kKeyring;
    // User scope because we're not root
    ref.scope = (uid == 0) ? rebuntu::environment::scope::ExecutionScope::kSystem : 
                             rebuntu::environment::scope::ExecutionScope::kUser;
    if (scope != rebuntu::environment::scope::ExecutionScope::kUser) {
        ref.scope = scope;
    }
    ref.key = std::move(key);
    ref.description = "user keyring entry";
    ref.should_redact = true;
    
    return ref;
}

SecretRef create_env_reference(
    std::string env_var_name,
    rebuntu::environment::scope::ExecutionScope scope) {
    
    SecretRef ref;
    ref.provider = SecretProvider::kEnv;
    ref.scope = scope;
    ref.key = std::move(env_var_name);
    ref.description = "environment variable";
    ref.should_redact = true;  // Environment variables often contain secrets
    
    return ref;
}

// ============================================================================
// SecretStore implementations (placeholders for future native integration)
// ============================================================================

namespace {

// Environment provider - reads from environment variables
class EnvSecretStore : public SecretStore {
public:
    SecretProvider provider() const override { return SecretProvider::kEnv; }
    
    bool is_available() const override { return true; }  // Always available
    
    SecretResolveResult resolve(const SecretRef& ref) override {
        if (ref.key.empty()) {
            return {
                .status = rebuntu::core::SemanticStatus::kFailure,
                .error_message = "empty key not allowed",
            };
        }
        
        const char* env_value = std::getenv(ref.key.c_str());
        if (!env_value) {
            return {
                .status = rebuntu::core::SemanticStatus::kUnknown,
                .error_message = "environment variable not found: " + ref.key,
            };
        }
        
        SecretResolveResult result;
        result.status = rebuntu::core::SemanticStatus::kSuccess;
        result.value = std::string(env_value);
        result.source_provider = SecretProvider::kEnv;
        
        return result;
    }
};

}  // namespace

// ============================================================================
// SecretStoreRegistry - Implementation
// ============================================================================

SecretStoreRegistry& SecretStoreRegistry::instance() {
    static SecretStoreRegistry registry;
    return registry;
}

void SecretStoreRegistry::register_store(std::unique_ptr<SecretStore> store) {
    if (store) {
        stores_[store->provider()] = std::move(store);
    }
}

SecretStore* SecretStoreRegistry::get_store(SecretProvider provider) const {
    auto it = stores_.find(provider);
    return (it != stores_.end()) ? it->second.get() : nullptr;
}

SecretResolveResult SecretStoreRegistry::resolve(const SecretRef& ref) {
    // Try to find the appropriate provider for this scope
    SecretStore* store = get_store(ref.provider);
    
    if (!store || !store->is_available()) {
        SecretResolveResult result;
        result.status = rebuntu::core::SemanticStatus::kUnknown;
        result.error_message = "provider not available: " + std::string(to_string(ref.provider));
        return result;
    }
    
    // Resolve the secret through the store
    return store->resolve(ref);
}

std::vector<SecretProvider> SecretStoreRegistry::get_available_providers(
    rebuntu::environment::scope::ExecutionScope /* scope */) const {
    std::vector<SecretProvider> providers;
    
    for (const auto& [provider, store] : stores_) {
        if (store->is_available()) {
            providers.push_back(provider);
        }
    }
    
    return providers;
}

// Initialize the registry with default stores
static struct RegistryInitializer {
    RegistryInitializer() {
        auto& reg = SecretStoreRegistry::instance();
        
        // Register environment store (always available for testing/debugging)
        reg.register_store(std::make_unique<EnvSecretStore>());
        
        // systemd and keyring stores will be added when native integration is complete
    }
} g_registry_initializer;

}  // namespace rebuntu::environment::secrets