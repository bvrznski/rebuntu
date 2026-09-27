#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-resolute}"
ARCH="${REBUNTU_ARCH:-amd64}"
TARGET="${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-$SUITE-$ARCH}"
OUT="$ROOT/build/artifacts/images"
mkdir -p "$OUT"
[[ -f "$TARGET/.rebuntu-rootfs" ]] || { echo "Build rootfs first." >&2; exit 1; }

name="rebuntu-rootfs-${SUITE}-${ARCH}.tar.zst"
sudo tar --xattrs --acls --numeric-owner -C "$TARGET" -cf - . | zstd -T0 -19 -o "$OUT/$name"
sudo chown "$(id -u):$(id -g)" "$OUT/$name"
sha256sum "$OUT/$name" > "$OUT/$name.sha256"
echo "Created: $OUT/$name"
