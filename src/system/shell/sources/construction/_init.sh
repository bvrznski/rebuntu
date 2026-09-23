# construction/ — Construction primitives
#
# Command construction and argument escaping utilities.

rebuntu_construct_command() {
    local cmd="$1"
    shift
    
    echo "$cmd $*"
}

rebuntu_escape_arg() {
    printf '%q' "$1"
}

rebuntu_quote_args() {
    local result=""
    for arg in "$@"; do
        if [[ -z "$result" ]]; then
            result="$(printf '%q' "$arg")"
        else
            result="$result $(printf '%q' "$arg")"
        fi
    done
    echo "$result"
}
