#!/usr/bin/env bash
# Safe one-off skeleton materializer. mkdir -p only; never deletes; operates
# only inside the project root; reports what it (would) create.
#   --dry-run  show what would be created without creating
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DRY=0
[[ "${1:-}" == "--dry-run" ]] && DRY=1
DIRS=( src/system/core src/system/shell src/system/runtime src/system/state
  src/system/environment bin cpp/include cpp/src cpp/tests docs/discoveries
  tests/unit tests/integration scripts config systemd examples experiments
  tools schemas packaging )
for d in "${DIRS[@]}"; do
  p="$ROOT/$d"
  if [[ -d "$p" ]]; then
    echo "exists  $d"
  elif (( DRY )); then
    echo "would   mkdir -p $d"
  else
    mkdir -p "$p"; echo "created $d"
  fi
done
echo "bootstrap complete (no deletions; project-root only)"
