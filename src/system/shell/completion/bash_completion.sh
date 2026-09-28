# rebuntu-shell-completion — Bash completion for Rebuntu CLI (Phase 6.13)
#
# This file provides bash completion support for the rebuntu command.
# It should be sourced into ~/.bashrc or loaded via /etc/bash_completion.d/
#
# Usage:
#   source /path/to/rebuntu/shell/completion/bash_completion.sh

# Only load if bash
[[ -z "$BASH_VERSION" ]] && return 1

# ============================================================================
# _rebuntu_get_verbs — Get list of available verbs from rebuntu binary
# ============================================================================

_rebuntu_get_verbs() {
    local rebuntu_bin="$(_rebuntu_find_binary)"
    
    if [[ -x "$rebuntu_bin" ]]; then
        # Query the rebuntu binary for available commands
        "$rebuntu_bin" help --json 2>/dev/null | jq -r '.verbs[].name' 2>/dev/null || \
        "$rebuntu_bin" inventory --help 2>&1 | grep "Commands:" -A 20 | awk '/^[[:space:]]+[a-z]/ {print $1}'
    fi
}

# ============================================================================
# _rebuntu_find_binary — Locate the rebuntu binary
# ============================================================================

_rebuntu_find_binary() {
    # Check PATH first
    local bin_path
    if command -v rebuntu >/dev/null 2>&1; then
        echo "$(command -v rebuntu)"
        return 0
    fi
    
    # Check common locations
    for location in \
        "/home/bvrznski/rebuntu/bin/rebuntu" \
        "/home/bvrznski/rebuntu/cpp/build/src/rebuntu-bin" \
        "/usr/local/bin/rebuntu" \
        "/usr/bin/rebuntu"; do
        
        if [[ -x "$location" ]]; then
            echo "$location"
            return 0
        fi
    done
    
    # Return empty string to indicate not found
    echo ""
}

# ============================================================================
# _rebuntu_complete_verb — Complete the verb (first positional argument)
# ============================================================================

_rebuntu_complete_verb() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    
    COMPREPLY=($(compgen -W "inventory status list start stop restart" -- "$cur"))
}

# ============================================================================
# _rebuntu_complete_inventory — Complete inventory subcommands
# ============================================================================

_rebuntu_complete_inventory() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    
    # Get context from previous words
    local prev_word="${COMP_WORDS[COMP_CWORD-1]}"
    
    case "$prev_word" in
        inventory)
            COMPREPLY=($(compgen -W "packages services processes" -- "$cur"))
            ;;
        packages|services|processes)
            # For target completion, we need to query the system
            # This should use rebuntu's discovery capabilities (bounded)
            COMPREPLY=()
            ;;
        *)
            COMPREPLY=($(compgen -W "packages services processes" -- "$cur"))
            ;;
    esac
}

# ============================================================================
# _rebuntu_complete_helper — Main completion dispatcher
# ============================================================================

_rebuntu_complete_helper() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    local prev_word="${COMP_WORDS[COMP_CWORD-1]}"
    
    case "${COMP_CWORD}" in
        0|1)
            # First word after 'rebuntu' - complete verbs
            COMPREPLY=($(compgen -W "inventory status list" -- "$cur"))
            ;;
        *)
            case "${COMP_WORDS[1]}" in
                inventory)
                    _rebuntu_complete_inventory
                    ;;
                *)
                    # Default: try to get verbs from binary if available
                    local rebuntu_bin="$(_rebuntu_find_binary)"
                    if [[ -n "$rebuntu_bin" && -x "$rebuntu_bin" ]]; then
                        COMPREPLY=($(compgen -W "$($rebuntu_bin help 2>&1 | awk '/^[[:space:]]*[a-z]/ {print $1}')" -- "$cur"))
                    fi
                    ;;
            esac
            ;;
    esac
    
    # Handle filenames (for paths that might follow commands)
    if [[ ${#COMPREPLY[@]} -eq 0 ]]; then
        COMPREPLY=($(compgen -f -- "$cur"))
    fi
}

# ============================================================================
# _rebuntu_complete — Main bash completion function for rebuntu command
# ============================================================================

_rebuntu_complete() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    
    # Reset COMPREPLY
    COMPREPLY=()
    
    # Skip if we're not completing a word
    [[ "$cur" == -* ]] && return 0
    
    case "${#COMP_WORDS[@]}" in
        2)
            # Completing first argument after 'rebuntu'
            local verbs="inventory status list start stop restart declare installed"
            COMPREPLY=($(compgen -W "$verbs" -- "$cur"))
            ;;
        *)
            local prev="${COMP_WORDS[COMP_CWORD-1]}"
            
            case "${COMP_WORDS[1]}" in
                inventory)
                    if [[ "$prev" == "inventory" ]]; then
                        # Complete inventory subcommands
                        COMPREPLY=($(compgen -W "packages services processes" -- "$cur"))
                    elif [[ "$prev" == "packages" || "$prev" == "services" || "$prev" == "processes" ]]; then
                        # For target completion, we could query the system but need to be bounded
                        # This is a placeholder - in production would use rebuntu discovery
                        :
                    fi
                    ;;
                packages)
                    if [[ "$prev" == "inventory" ]]; then
                        COMPREPLY=($(compgen -W "packages services processes" -- "$cur"))
                    else
                        # Target completion (bounded)
                        COMPREPLY=()
                    fi
                    ;;
                start|stop|restart)
                    if [[ "$prev" == "service" || "$prev" == "services" ]]; then
                        # Service target completion - bounded by max 100 services
                        local max_services=100
                        local services=$(systemctl list-units --type=service --no-legend 2>/dev/null | awk '{print $1}' | head -n $max_services)
                        COMPREPLY=($(compgen -W "$services" -- "$cur"))
                    fi
                    ;;
                declare|installed)
                    # Predicate completion - no target needed usually
                    ;;
            esac
            ;;
    esac
    
    # If we have results, sort and deduplicate
    if [[ ${#COMPREPLY[@]} -gt 0 ]]; then
        COMPREPLY=($(printf '%s\n' "${COMPREPLY[@]}" | sort -u))
    fi
    
    # Use readline's default file completion as fallback
    compopt -o filenames 2>/dev/null || true
}

# ============================================================================
# Install the completion
# ============================================================================

complete -F _rebuntu_complete rebuntu 2>/dev/null || true
complete -F _rebuntu_complete_helper rebuntu-bin 2>/dev/null || true