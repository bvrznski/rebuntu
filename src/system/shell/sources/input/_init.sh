# input/ — Input handling utilities
rebuntu_input_readline() { local p="${1:-}"; [[ -n "$p" ]] && printf "%s" "$p"; read -r line; echo "$line"; }
rebuntu_input_prompt() { local q="$1" d="${2:-}"; if [[ -t 0 ]]; then [[ -n "$d" ]] && read -r -p "${q} [$d]: " i || read -r -p "${q}: " i; echo "${i:-$d}"; else [[ -n "$d" ]] && echo "$d" || return 1; fi; }
rebuntu_input_is_terminal() { [[ -t 0 ]]; }
