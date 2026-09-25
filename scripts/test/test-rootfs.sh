#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-jammy}"
ARCH="${REBUNTU_ARCH:-amd64}"
TARGET="${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-$SUITE-$ARCH}"

fail(){ echo "FAIL: $*" >&2; exit 1; }

[[ -f "$TARGET/.rebuntu-rootfs" ]] || fail "rootfs marker missing"
grep -q '^ID=rebuntu$' "$TARGET/usr/lib/os-release" || fail "ID is not rebuntu"
grep -q '^ID_LIKE="ubuntu debian"$' "$TARGET/usr/lib/os-release" || fail "ancestry missing"
[[ "$(cat "$TARGET/etc/hostname")" == "rebuntu" ]] || fail "hostname"
[[ -f "$TARGET/etc/rebuntu-release" ]] || fail "/etc/rebuntu-release missing"

for pkg in rebuntu-release rebuntu-branding rebuntu-plymouth-theme rebuntu-base; do
  sudo chroot "$TARGET" dpkg-query -W -f='${Status}\n' "$pkg" 2>/dev/null |
    grep -q 'install ok installed' || fail "$pkg not installed"
done

echo "PASS: Rebuntu rootfs identity and foundation packages"
