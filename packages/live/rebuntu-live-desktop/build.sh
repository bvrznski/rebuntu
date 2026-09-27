#!/usr/bin/env bash
set -Eeuo pipefail

D="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$D/../../.." && pwd)"
OUT="$ROOT/build/artifacts/deb"

STAGE="$(mktemp -d)"
trap 'rm -rf "$STAGE"' EXIT

mkdir -p "$OUT"

cp -a "$D/." "$STAGE/"
rm -f "$STAGE/build.sh"

dpkg-deb \
    --root-owner-group \
    --build \
    "$STAGE" \
    "$OUT/rebuntu-live-desktop_0.1.0-1_all.deb"

echo "Built rebuntu-live-desktop"
