#!/usr/bin/env bash
set -Eeuo pipefail

D="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
R="$(cd "$D/../../.." && pwd)"
OUT="$R/build/artifacts/deb"

STAGE="$(mktemp -d)"
trap 'rm -rf "$STAGE"' EXIT

mkdir -p "$OUT"

cp -a "$D/." "$STAGE/"
rm -f "$STAGE/build.sh"

dpkg-deb \
    --root-owner-group \
    --build \
    "$STAGE" \
    "$OUT/rebuntu-desktop_0.1.0-1_all.deb"

echo "Built rebuntu-desktop"
