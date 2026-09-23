# output/ — Output formatting utilities
rebuntu_output_format() { local f="$1"; shift; case "$f" in json) printf '{"output": "%s"}\n' "$(printf '%s\n' "$@" | tr '\n' ' ')';; table) echo "$*" | tr ' ' '|';; *) printf '%s\n' "$@";; esac; }
rebuntu_output_error() { local m="$1"; echo "ERROR: $m" >&2; }
rebuntu_output_progress() { local c="${1:-0}" t="${2:-100}"; [[ $t -gt 0 ]] && printf "\rProgress: %3d%% (%d/%d)" "$((c*100/t))" "$c" "$t" || printf "Progress: %d" "$c"; }
rebuntu_output_table() { local h="$1"; shift; echo "$h" | tr ' ' '|'; echo "---|---|---"; printf '%s\n' "$@"; }
