# processes/ — Process inspection and control
rebuntu_process_exists() { local pid="$1"; [[ -d "/proc/$pid" ]] || kill -0 "$pid" 2>/dev/null; }
rebuntu_process_state() { local pid="$1"; if [[ -f "/proc/$pid/stat" ]]; then awk '{print $3}' < "/proc/$pid/stat" 2>/dev/null; elif command -v ps &>/dev/null; then ps -o state= -p "$pid" 2>/dev/null | tr -d ' '; else echo "unknown"; fi; }
rebuntu_process_signal() { local pid="$1" sig="${2:-TERM}"; rebuntu_process_exists "$pid" && kill "-$sig" "$pid" 2>/dev/null || { echo "Error: Process $pid does not exist" >&2; return 1; }; }
