# coordination/ — Coordination primitives
rebuntu_coord_with_lock() { local lockfile="$1"; shift; flock -n 200 "$lockfile" "$@" || return 1; }
rebuntu_coord_atomic_group() { local failed=0; for cmd in "$@"; do eval "$cmd" || failed=1; done; return $failed; }
