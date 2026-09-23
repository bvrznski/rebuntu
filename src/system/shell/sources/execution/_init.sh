# execution/ — Command execution wrappers
rebuntu_exec_with_timeout() { local t="${1:-30}"; shift; timeout "$t" "$@"; }
rebuntu_exec_validate() { [[ -n "$1" ]] && eval "$1" || return 1; shift; "$@"; }
rebuntu_exec_verify() { local cmd="$1" ver="${2:-true}"; eval "$cmd"; local e=$?; [[ $e -eq 0 ]] && eval "$ver" && return 0 || { echo "Verification failed: $cmd" >&2; return 1; }; return $e; }
