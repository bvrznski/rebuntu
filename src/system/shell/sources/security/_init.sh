# security/ — Security-aware helpers
rebuntu_security_has_capability() { [[ $EUID -eq 0 ]]; }
rebuntu_security_can_access() { local p="$1" m="${2:-r}"; case "$m" in r) [[ -r "$p" ]];; w) [[ -w "$p" ]];; x) [[ -x "$p" ]];; *) return 1;; esac; }
rebuntu_security_require_root() { [[ $EUID -ne 0 ]] && { echo "Error: Root privilege required" >&2; return 1; }; }
