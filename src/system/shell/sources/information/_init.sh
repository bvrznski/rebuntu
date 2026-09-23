# information/ — Information and observation helpers
rebuntu_info_getprop() { local f="$1" k="$2"; [[ -f "$f" ]] && grep "^${k}=" "$f" 2>/dev/null | cut -d= -f2-; }
rebuntu_info_available_tools() { for cmd in "$@"; do command -v "$cmd" &>/dev/null && echo "$cmd"; done; }
rebuntu_info_current_state() { local r="$1"; case "$r" in hostname) hostname 2>/dev/null || echo "unknown";; os) grep "^PRETTY_NAME=" /etc/os-release 2>/dev/null | cut -d= -f2- | tr -d '"';; *) echo "unknown";; esac; }
