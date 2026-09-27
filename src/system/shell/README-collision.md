# Collision Governance and Shell Integration — Phase 6.10

## Shell Command Collision Policy

Rebuntu commands must coexist with existing Unix shell builtins, system commands, and user-defined functions/aliases.

### Classification Categories

| Category | Description | Rebuntu Action |
|----------|-------------|----------------|
| FREE | Not reserved by any system | Rebuntu may use this verb |
| REBUNTU | Reserved for Rebuntu internal use | Rebuntu exclusive |
| SHELL_BUILTIN | Shell built-in commands (bash, zsh) | Rebuntu MUST NOT shadow; require explicit prefix |
| SYSTEM_COMMAND | Installed system utilities | Warn user in help output |
| USER_DEFINED | User aliases/functions | Preserve and warn if detected |

### Reserved Verbs

The following verbs are reserved for Rebuntu shell use:
- `list`, `status`, `installed`, `running`, `declared`, etc.

### Shell Builtins (SHADOWING PROHIBITED)

Rebuntu MUST NOT shadow these commands. Use explicit prefix when calling:

| Command | Shell | Action |
|---------|-------|--------|
| cd, pwd, export, unset | bash/zsh | Require `rebuntu <verb>` form |
| source, alias, unalias | bash/zsh | Require `rebuntu <verb>` form |
| read, write | bash/zsh | Require `rebuntu <verb>` form |
| test, [, [[ ] | bash/zsh | Require explicit prefix |

### System Commands (WARN IF DETECTED)

Rebuntu commands that may collide with system utilities:

| Command | Typical Source | Rebuntu Response |
|---------|----------------|------------------|
| find, grep, awk, sed | GNU coreutils | Show warning in help |
| mount, umount | util-linux | Show warning in help |
| kill, ps, top | procps / psmisc | Show warning in help |

### User Aliases (PRESERVE AND WARN)

When user-defined aliases/functions are detected:

1. Detect via `type -a <verb>`
2. Record collision status in CommandMetadata
3. Show warning if collision would affect Rebuntu usage
4. Always provide explicit `rebuntu <verb>` fallback

## Collision Detection Implementation

### Shell Integration (Phase 6.11+)

```bash
# Example shell integration script
_rebuntu_detect_collision() {
    local verb="$1"
    
    # Check for bash builtins first
    if command -v "$verb" > /dev/null 2>&1; then
        local cmd_type=$(type -t "$verb")
        
        case "$cmd_type" in
            builtin)
                echo "REBUNTU_BUILTIN_COLLISION:$verb"
                ;;
            file|alias|function)
                # Check if it's a Rebuntu command
                local full_path=$(command -v "$verb")
                if [[ "$full_path" == *rebuntu* ]]; then
                    echo "REBUNTU_COMMAND:$verb"
                else
                    echo "SYSTEM_COLLISION:$verb:$full_path"
                fi
                ;;
            *)
                echo "FREE:$verb"
                ;;
        esac
    else
        echo "FREE:$verb"
    fi
}
```

### Detection Flow

1. **At Shell Load Time**:
   - Scan known Rebuntu verbs against `command -v` output
   - Record collision status in metadata registry
   - Output warning for critical collisions

2. **At Runtime (Command Resolution)**:
   - Check collision status before command dispatch
   - If collision detected and would cause ambiguity:
     - Show diagnostic message
     - Suggest explicit `rebuntu <verb>` form
     - May fail with error in strict mode

## Collision Detection API

```cpp
// Phase 6.10+ extension to types.hpp
enum class CollisionStatus {
    kNone,          // No collision detected
    kShellBuiltin,  // Collides with shell builtin
    kSystemCommand, // Collides with installed system command
    kUserAlias,     // Collides with user-defined alias/function
    kAmbiguous,     // Multiple matches for abbreviation
};

struct CommandMetadata {
    // ... existing fields ...
    
    CollisionStatus collision_status{CollisionStatus::kNone};
    std::optional<std::string> collision_with;  // Name of colliding command
};
```

## Strict Mode Behavior

When `strict_mode` is enabled:
- Ambiguous collisions cause immediate failure
- User must use explicit `rebuntu <verb>` form
- No interactive disambiguation prompts

## Example Collision Handling

```bash
# Scenario: user has 'ls' aliased to something different than Rebuntu's list command

$ type -a ls
ls is /bin/ls
ls is aliased to `ls --color=auto'

# Rebuntu's 'list' verb does not collide with 'ls'
# No action needed

# Scenario: user has 'test' aliased (collides with bash builtin)

$ type -a test
test is a shell builtin
test is /usr/bin/test

# Rebuntu must NOT shadow 'test' or '!'
# If Rebuntu needs to query state, use explicit form:
$ rebuntu status package foo
```

## Collision Report Format

```json
{
    "timestamp": "2026-09-28T...",
    "collisions": [
        {
            "verb": "test",
            "type": "shell_builtin",
            "source": "bash",
            "rebuntu_uses": null,
            "action": "skip"
        },
        {
            "verb": "find",
            "type": "system_command",
            "source": "/usr/bin/find",
            "rebuntu_uses": null,
            "action": "warn"
        }
    ]
}
```

## Shell Completion Integration (Phase 6.11+)

```bash
# Bash completion hook for rebuntu commands

_rebuntu_complete() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    
    # Get list of known verbs from Rebuntu
    local verbs=$(rebuntu help --json | jq -r '.verbs[].name')
    
    COMPREPLY=($(compgen -W "$verbs" -- "$cur"))
}

complete -F _rebuntu_complete rebuntu
```

## Documentation Requirements

Every Rebuntu command must document:
1. Collision status (FREE, SHELL_BUILTIN, SYSTEM_COMMAND, etc.)
2. Recommended usage form when collision exists
3. Alternative forms available in Rebuntu

## Future Work (Phase 6.11+)

- [ ] Full stdin reader with TTY detection and timeout
- [ ] SIGPIPE signal handling for broken pipes
- [ ] Completion hooks (bash/zsh)
- [ ] Shell function wrapper generation
- [ ] User alias detection at runtime