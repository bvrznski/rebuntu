#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SRC="$ROOT/packages/branding/rebuntu-plymouth-theme"
OUT="$ROOT/build/artifacts/deb"

mkdir -p "$OUT"
dpkg-deb --root-owner-group --build "$SRC" "$OUT/rebuntu-plymouth-theme_0.1.0_all.deb"
echo "Created: $OUT/rebuntu-plymouth-theme_0.1.0_all.deb"
