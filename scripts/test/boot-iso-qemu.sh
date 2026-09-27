#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-resolute}"
ARCH="${REBUNTU_ARCH:-amd64}"
ISO="${1:-$ROOT/build/artifacts/images/rebuntu-$SUITE-$ARCH.iso}"
[[ -s "$ISO" ]] || { echo "ISO missing: $ISO" >&2; exit 1; }
command -v qemu-system-x86_64 >/dev/null || { echo "Install qemu-system-x86." >&2; exit 1; }

exec qemu-system-x86_64 \
  -enable-kvm -machine q35 -cpu host -m 4096 -smp 4 \
  -cdrom "$ISO" -boot d -device virtio-vga -display gtk
