#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

ISO="${1:-$ROOT/build/artifacts/images/rebuntu-jammy-amd64.iso}"

[[ -s "$ISO" ]] || {
    echo "FAIL: ISO missing: $ISO" >&2
    exit 1
}

command -v xorriso >/dev/null || {
    echo "ERROR: xorriso required" >&2
    exit 2
}

LIST="$(
    xorriso \
        -indev "$ISO" \
        -find / -type f -print \
        2>/dev/null
)"

for path in \
    /casper/vmlinuz \
    /casper/initrd \
    /casper/filesystem.squashfs \
    /boot/grub/grub.cfg \
    /EFI/BOOT/BOOTX64.EFI
do
    grep -Fxq "$path" <<<"$LIST" || {
        echo "FAIL: ISO missing $path" >&2
        exit 1
    }

    echo "PASS  $path"
done

ELTORITO="$(
    xorriso \
        -indev "$ISO" \
        -report_el_torito as_mkisofs \
        2>/dev/null
)"

grep -q \
    -- "-b '/boot/grub/bios.img'" \
    <<<"$ELTORITO"

grep -q \
    -- "-e '/EFI/efiboot.img'" \
    <<<"$ELTORITO"

echo "PASS  BIOS El Torito"
echo "PASS  UEFI El Torito"
echo "PASS  ISO structure"
