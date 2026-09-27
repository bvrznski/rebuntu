#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

TARGET="${1:-${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-resolute-amd64}}"

sudo test -d \
    "$TARGET/opt/rebuntu/repository"

sudo grep -q \
    'file:/opt/rebuntu/repository' \
    "$TARGET/etc/apt/sources.list.d/rebuntu-local.list"

echo "PASS  embedded Rebuntu repository"
