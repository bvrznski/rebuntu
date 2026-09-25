#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-jammy}"
ARCH="${REBUNTU_ARCH:-amd64}"
ISO="${1:-$ROOT/build/artifacts/images/rebuntu-$SUITE-$ARCH.iso}"
[[ -s "$ISO" ]] || { echo "FAIL: ISO missing: $ISO" >&2; exit 1; }

listing="$(xorriso -indev "$ISO" -find / -type f -print 2>/dev/null)"
for f in /casper/vmlinuz /casper/initrd /casper/filesystem.squashfs /boot/grub/grub.cfg /EFI/BOOT/BOOTX64.EFI; do
  grep -Fxq "$f" <<<"$listing" || { echo "FAIL: missing $f" >&2; exit 1; }
done
echo "PASS: live ISO contains kernel, initrd, SquashFS, GRUB and UEFI loader."
