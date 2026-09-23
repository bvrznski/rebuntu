# flow/ — Pipeline and flow control utilities
#
# Pipeline composition primitives that enable shell-native workflow construction.
# The goal is to provide semantic abstractions over native shell pipes.

# Pipe command output to clipboard (abstracts Wayland/X11 differences)
# INPUT:  stdin or argument string
# OUTPUT: Nothing (data sent to clipboard)
# EXAMPLE: echo "hello" | rebuntu_clip
#          rebuntu_clip "hello"
rebuntu_clip() {
    local input=""
    
    # Check if we have stdin input
    if [[ ! -t 0 ]]; then
        # Read from stdin
        input=$(cat)
    fi
    
    # If no stdin, check for argument input
    if [[ -z "$input" && $# -gt 0 ]]; then
        input="$*"
    fi
    
    # Try different clipboard utilities based on what's available
    if command -v wl-copy &>/dev/null; then
        # Wayland (GNOME on Wayland, KDE Plasma)
        echo -n "$input" | wl-copy 2>/dev/null && return 0
        
    elif command -v xclip &>/dev/null; then
        # X11 with xclip
        echo -n "$input" | xclip -selection clipboard 2>/dev/null && return 0
        
    elif command -v xsel &>/dev/null; then
        # X11 with xsel
        echo -n "$input" | xsel --clipboard --input 2>/dev/null && return 0
        
    elif command -v pbcopy &>/dev/null; then
        # macOS
        echo -n "$input" | pbcopy 2>/dev/null && return 0
        
    else
        echo "Error: No clipboard utility available (tried wl-copy, xclip, xsel, pbcopy)" >&2
        return 1
    fi
}

# Redirect stdout to a file or command with cleanup on error
# INPUT:  Output path/command, then command to run
# OUTPUT: Result of the command
rebuntu_pipe_to() {
    local target="$1"
    shift
    
    if [[ -z "$target" ]]; then
        echo "Error: No target specified for rebuntu_pipe_to" >&2
        return 1
    fi
    
    # Execute command and capture output
    local result
    result=$(eval "$@" 2>&1)
    local exit_code=$?
    
    if [[ $exit_code -eq 0 ]]; then
        echo "$result" | rebuntu_clip "$target"
    else
        echo "$result" >&2
    fi
    
    return $exit_code
}

# Chain commands with success condition (only run if previous succeeded)
# INPUT:  Commands to chain
# OUTPUT: Result of last successful command, or early failure
rebuntu_chain_if_success() {
    local exit_code=0
    
    for cmd in "$@"; do
        if [[ $exit_code -eq 0 ]]; then
            eval "$cmd"
            exit_code=$?
        fi
    done
    
    return $exit_code
}

# Run command and capture stderr separately from stdout
# INPUT:  Command to run
# OUTPUT: stdout to stdout, stderr to file descriptor 3
rebuntu_with_stderr() {
    local output_file="/tmp/rebuntu_stderr_$$.tmp"
    
    # Run command with stderr redirected to temp file
    "$@" > /dev/stdout 2>"$output_file"
    local exit_code=$?
    
    # Output stderr if file exists and has content
    if [[ -s "$output_file" ]]; then
        cat "$output_file" >&3
    fi
    
    rm -f "$output_file"
    
    return $exit_code
}

# Buffer stdin until a condition is met, then output all at once
# This prevents interleaved output when running parallel commands
rebuntu_buffer() {
    local buffer=""
    local line
    
    while IFS= read -r line || [[ -n "$line" ]]; do
        buffer+="$line"$'\n'
    done
    
    # Output at end (one write operation)
    printf "%s" "$buffer"
}