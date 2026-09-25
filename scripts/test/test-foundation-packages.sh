#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ART="$ROOT/build/artifacts/deb"

failed=0
for deb in "$ART"/*.deb; do
  [[ -e "$deb" ]] || continue
  echo "==> $deb"
  dpkg-deb --info "$deb" >/dev/null || failed=1
  dpkg-deb --contents "$deb" | head -n 30 || true
done
exit "$failed"
