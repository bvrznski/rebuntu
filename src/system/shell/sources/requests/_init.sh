# requests/ — Request primitives
rebuntu_request_build() { local op="$1"; shift; local t="" p=""; while [[ $# -gt 0 ]]; do case "$1" in --target|-t) t="$2"; shift 2;; *) [[ -z "$p" ]] && p="$1" || p="$p $1"; shift;; esac; done; echo "operation=${op}"; [[ -n "$t" ]] && echo "target=${t}"; [[ -n "$p" ]] && echo "parameters=${p}"; }
rebuntu_request_invoke() { local r="$1"; echo "Request invoked: $r"; return 0; }
