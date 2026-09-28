#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
SRC="$ROOT/packages/installer/rebuntu-installer"
OUT="$ROOT/build/artifacts/deb"
STAGE="$(mktemp -d)"

cleanup() {
    rm -rf "$STAGE"
}
trap cleanup EXIT

mkdir -p "$OUT"

cp -a "$SRC/." "$STAGE/"
rm -f "$STAGE/build.sh"

chmod 0755 \
    "$STAGE/usr/lib/rebuntu/installer/prepare-subiquity"

dpkg-deb \
    --root-owner-group \
    --build \
    "$STAGE" \
    "$OUT/rebuntu-installer_0.1.0-1_all.deb"

echo "Built: $OUT/rebuntu-installer_0.1.0-1_all.deb"
