# filesystem/ — Filesystem operations
rebuntu_fs_read() { local p="$1"; [[ -r "$p" ]] && cat "$p" || { echo "Error: Cannot read $p" >&2; return 1; }; }
rebuntu_fs_write() { local p="$1" t="${p}.$$"; shift; cat > "$t" && mv "$t" "$p" || { rm -f "$t"; echo "Error writing $p" >&2; return 1; }; }
rebuntu_fs_exists_type() { local p="$1" e="${2:-}"; [[ ! -e "$p" ]] && return 1; case "$e" in f|-) [[ -f "$p" ]];; d) [[ -d "$p" ]];; l|symlink) [[ -L "$p" ]];; *) return 0;; esac; }
rebuntu_fs_size() { local p="$1"; [[ -f "$p" ]] && stat -c %s "$p" 2>/dev/null || echo "0"; }
