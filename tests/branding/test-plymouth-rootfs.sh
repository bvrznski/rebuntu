#!/usr/bin/env bash
set -Eeuo pipefail

TARGET="${REBUNTU_ROOTFS:-/work/rootfs}"
THEME="$TARGET/usr/share/plymouth/themes/rebuntu/rebuntu.plymouth"

test -s "$THEME" || {
    echo "Theme missing from rootfs: $THEME" >&2
    exit 1
}

KERNEL="$(find "$TARGET/boot" -maxdepth 1 -type f -name 'vmlinuz-*' | sort -V | tail -n1)"
test -n "$KERNEL"
KVER="${KERNEL##*/vmlinuz-}"
INITRD="$TARGET/boot/initrd.img-$KVER"
test -s "$INITRD"

# lsinitramfs is intentionally executed outside the chroot.
if command -v lsinitramfs >/dev/null 2>&1; then
    if sudo lsinitramfs "$INITRD" | grep -q 'usr/share/plymouth/themes/rebuntu/rebuntu'; then
        echo "Rebuntu Plymouth rootfs/initramfs test: PASS"
    else
        echo "Theme exists in rootfs but was not found in initramfs." >&2
        exit 1
    fi
else
    echo "Theme exists; lsinitramfs unavailable, initramfs content check skipped."
fi
