# configuration/ — Configuration access utilities
#
# Shell-native configuration access: reading values from canonical config.

# Get value from environment variable with default
rebuntu_config_get() {
    local key="$1"
    local default="${2:-}"
    
    echo "${!key:-$default}"
}

# Check if a configuration key exists
rebuntu_config_exists() {
    local key="$1"
    
    [[ -n "${!key:-}" ]]
}

# Get environment variable (wrapper with explicit naming)
rebuntu_env_get() {
    local name="$1"
    local default="${2:-}"
    
    echo "${!name:-$default}"
}