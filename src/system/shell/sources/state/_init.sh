# state/ — Shell state management
rebuntu_state_set() { local k="$1"; shift; export "REBUNTU_STATE_${k}=$(printf '%s\n' "$@")"; }
rebuntu_state_get() { local k="$1"; echo "${REBUNTU_STATE_${k}:-}"; }
rebuntu_state_clear() { for v in $(env | grep '^REBUNTU_STATE_'); do unset "${v%%=*}"; done; }
