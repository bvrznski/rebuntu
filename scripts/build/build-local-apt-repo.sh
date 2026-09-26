#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ART="$ROOT/build/artifacts/deb"
REPO="$ROOT/repository/local"
mkdir -p "$REPO"

cp -f "$ART"/*.deb "$REPO/" 2>/dev/null || true

command -v dpkg-scanpackages >/dev/null 2>&1 || {
  echo "dpkg-scanpackages missing; install dpkg-dev" >&2
  exit 1
}

(
  cd "$REPO"
  dpkg-scanpackages . /dev/null > Packages
  gzip -9c Packages > Packages.gz
)

echo "Local repository built: $REPO"
echo "Temporary test source:"
echo "  deb [trusted=yes] file:$REPO ./"
