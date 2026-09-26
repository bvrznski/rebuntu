#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
OUT="$ROOT/build/artifacts/deb"

mkdir -p "$OUT"

dpkg-deb \
    --root-owner-group \
    --build \
    "$ROOT/packages/live/rebuntu-live-desktop" \
    "$OUT/rebuntu-live-desktop_0.1.0-1_all.deb"

echo "Built rebuntu-live-desktop"
