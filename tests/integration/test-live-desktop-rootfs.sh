#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

SUITE="${UBUNTU_SUITE:-resolute}"
ARCH="${REBUNTU_ARCH:-amd64}"

TARGET="${1:-${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-$SUITE-$ARCH}}"

FILES=(
    "$TARGET/.rebuntu-rootfs"
    "$TARGET/usr/bin/gnome-shell"
    "$TARGET/usr/sbin/gdm3"
    "$TARGET/usr/share/wayland-sessions/rebuntu.desktop"
    "$TARGET/usr/share/xsessions/rebuntu-xorg.desktop"
    "$TARGET/etc/gdm3/custom.conf"
    "$TARGET/etc/sudoers.d/90-rebuntu-live"
    "$TARGET/etc/apt/sources.list.d/rebuntu-local.list"
)

for file in "${FILES[@]}"; do
    if sudo test -e "$file"; then
        echo "PASS  $file"
    else
        echo "FAIL  $file" >&2
        exit 1
    fi
done

sudo chroot "$TARGET" \
    id rebuntu >/dev/null

sudo chroot "$TARGET" \
    dpkg-query \
    -W \
    -f='${Status}\n' \
    rebuntu-live-desktop |
    grep -qx 'install ok installed'

echo "PASS  live desktop rootfs"
