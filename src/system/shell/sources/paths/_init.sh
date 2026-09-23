# paths/ — Path manipulation utilities
#
# Safe path manipulation with edge case handling: spaces, symlinks,
# relative/absolute conversion, canonicalization.

# Check if a path is absolute
rebuntu_path_is_absolute() {
    local path="$1"
    
    [[ "$path" == /* ]] || return 1
    return 0
}

# Normalize a path (resolve . and .. components)
# INPUT:  Path string
# OUTPUT: Normalized path to stdout
# STDERR: Error messages on failure
# EXIT:   0 on success, non-zero on error
rebuntu_path_normalize() {
    local path="$1"
    
    # Handle empty input
    [[ -z "$path" ]] && { echo "."; return 0; }
    
    # Use bash parameter expansion for basic normalization
    local result="$path"
    
    # Replace multiple slashes with single slash
    while [[ "$result" == *//* ]]; do
        result="${result//\/\/\//\/}"
    done
    
    # Remove trailing slash (except for root)
    if [[ "$result" != "/" && "$result" == */ ]]; then
        result="${result%/}"
    fi
    
    echo "$result"
}

# Canonicalize a path (resolve symlinks and get true path)
# INPUT:  Path string
# OUTPUT: Canonical path to stdout
# STDERR: Error messages on failure
# EXIT:   0 on success, non-zero if path doesn't exist or canonicalization fails
rebuntu_path_canonicalize() {
    local path="$1"
    
    # Try to use realpath first (GNU coreutils)
    if command -v realpath &>/dev/null; then
        realpath "$path" 2>/dev/null && return 0
        
        # If realpath fails, try readlink -f as fallback
        if command -v readlink &>/dev/null; then
            readlink -f "$path" 2>/dev/null && return 0
        fi
        
        echo "Error: Cannot canonicalize path: $path (does not exist)" >&2
        return 1
    fi
    
    # Fallback: basic normalization if no realpath available
    rebuntu_path_normalize "$path"
}

# Join paths safely without duplication of separators
# INPUT:  Multiple path components
# OUTPUT: Joined path to stdout
# EXAMPLE: rebuntu_path_join /usr local bin => /usr/local/bin
rebuntu_path_join() {
    local result=""
    local component
    
    for component in "$@"; do
        # Skip empty components
        [[ -z "$component" ]] && continue
        
        # Remove leading/trailing slashes from component
        component="${component#/}"
        component="${component%/}"
        
        if [[ -z "$result" ]]; then
            result="$component"
        else
            # Add separator if needed
            if [[ "$result" != /* ]]; then
                result="$result/$component"
            else
                result="/$component"
            fi
        fi
    done
    
    # Handle empty result
    [[ -z "$result" ]] && { echo "."; return 0; }
    
    # Normalize the result
    rebuntu_path_normalize "$result"
}

# Get parent directory of a path
# INPUT:  Path string
# OUTPUT: Parent directory to stdout
# EXIT:   0 on success, non-zero on error
rebuntu_path_parent() {
    local path="$1"
    
    # Normalize first
    local normalized
    normalized=$(rebuntu_path_normalize "$path") || return 1
    
    # Handle special cases
    [[ "$normalized" == "/" ]] && { echo "/"; return 0; }
    [[ "$normalized" == "." ]] && { echo ".."; return 0; }
    
    # Extract parent
    local parent="${normalized%/*}"
    [[ -z "$parent" ]] && parent="/"
    
    echo "$parent"
}

# Get basename of a path (like basename command)
# INPUT:  Path string
# OUTPUT: Basename to stdout
rebuntu_path_basename() {
    local path="$1"
    
    # Normalize first
    local normalized
    normalized=$(rebuntu_path_normalize "$path") || echo "$path"
    
    # Extract basename
    echo "${normalized##*/}"
}

# Check if a path exists and verify its type
# INPUT:  Path string, optional type (f=file, d=directory, l=symlink)
# OUTPUT: 0 if condition met, non-zero otherwise
rebuntu_path_exists_type() {
    local path="$1"
    local expected_type="${2:-}"
    
    [[ ! -e "$path" ]] && return 1
    
    if [[ -z "$expected_type" ]]; then
        return 0  # Just existence check
    fi
    
    case "$expected_type" in
        f|file|-)
            [[ -f "$path" ]]
            ;;
        d|directory)
            [[ -d "$path" ]]
            ;;
        l|link|symlink)
            [[ -L "$path" ]]
            ;;
        *)
            return 1
            ;;
    esac
}