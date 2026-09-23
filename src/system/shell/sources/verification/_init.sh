# verification/ — Postcondition verification helpers
rebuntu_verify_exists() { local p="$1"; [[ -e "$p" ]]; }
rebuntu_verify_file_contains() { local p="$1" e="$2"; grep -qF "$e" "$p" 2>/dev/null; }
rebuntu_verify_state() { local a="$1" ex="$2"; [[ "$a" == "$ex" ]]; }
rebuntu_verify_output() { local o="$1" pat="$2"; echo "$o" | grep -qE "$pat" 2>/dev/null; }
