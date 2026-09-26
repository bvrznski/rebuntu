#!/usr/bin/env bash
# Deterministic live-boot smoke test for the Rebuntu ISO.
#
# Proves the machine progresses beyond GRUB and reaches a recognizable
# live-userspace milestone (systemd + getty/login on a serial console) -- i.e.
# it does NOT drop to the initramfs emergency shell and does NOT kernel-panic.
#
# Design notes:
#  - We boot the ISO's OWN kernel + initrd (extracted from the ISO) with the CD
#    attached, so casper discovers /casper/filesystem.squashfs exactly as a user
#    boot does. A serial console (console=ttyS0) is enabled for diagnostics,
#    which the project policy explicitly permits for testing while production
#    keeps "boot=casper quiet splash ---".
#  - Success  = a live-userspace milestone marker is seen on serial.
#  - Failure  = a hard failure marker (kernel panic / emergency shell) is seen,
#               OR no userspace milestone appears within the bounded timeout.
#
# Usage: boot-live-serial.sh <iso> <bios|uefi> [timeout_seconds]

set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ISO="${1:?usage: boot-live-serial.sh <iso> <bios|uefi> [timeout]}"
MODE="${2:-bios}"
TIMEOUT="${3:-180}"
WORK="$ROOT/build/boot-test/$(basename "$ISO").$MODE"
SERIAL="$WORK/serial.log"

command -v qemu-system-x86_64 >/dev/null || { echo "FAIL: qemu-system-x86_64 missing" >&2; exit 2; }
[[ -s "$ISO" ]] || { echo "FAIL: ISO missing: $ISO" >&2; exit 2; }

rm -rf "$WORK"; mkdir -p "$WORK"

# --- Extract the ISO's own kernel + initrd (cached per ISO+mode) --------------
if [[ ! -s "$WORK/vmlinuz" || ! -s "$WORK/initrd" ]]; then
  xorriso -osirrox on -indev "$ISO" -extract /casper/vmlinuz "$WORK/vmlinuz" 2>/dev/null \
    || { echo "FAIL: cannot extract /casper/vmlinuz" >&2; exit 2; }
  xorriso -osirrox on -indev "$ISO" -extract /casper/initrd "$WORK/initrd" 2>/dev/null \
    || { echo "FAIL: cannot extract /casper/initrd" >&2; exit 2; }
fi

# --- Build the QEMU invocation ------------------------------------------------
COMMON=(
  -enable-kvm -cpu host -m 4096 -smp 4
  -display none -monitor none
  -cdrom "$ISO" -boot d
  -kernel "$WORK/vmlinuz" -initrd "$WORK/initrd"
  -append "boot=casper quiet splash console=ttyS0,115200n8 ---"
  -serial file:"$SERIAL"
  -no-reboot
)
case "$MODE" in
  bios) ARGS=(qemu-system-x86_64 -machine q35 "${COMMON[@]}") ;;
  uefi)
    OVMF="/usr/share/ovmf/OVMF.fd"
    [[ -f "$OVMF" ]] || { echo "SKIP: OVMF not available ($OVMF)" >&2; exit 3; }
    ARGS=(qemu-system-x86_64 -machine q35 -drive if=pflash,format=raw,file="$OVMF",unit=0,readonly=on \
          -drive if=pflash,format=raw,file="$OVMF",unit=1,readonly=on "${COMMON[@]}")
    ;;
  *) echo "FAIL: unknown mode $MODE" >&2; exit 2 ;;
esac

# --- Boot with a bounded timeout ---------------------------------------------
echo "=== Boot test: $MODE (timeout ${TIMEOUT}s) ==="
start=$(date +%s)
timeout --signal=KILL "$TIMEOUT" "${ARGS[@]}" >/dev/null 2>&1
rc=$?
elapsed=$(( $(date +%s) - start ))

# --- Classify the result from the serial log ---------------------------------
fail=0
if [[ -s "$SERIAL" ]]; then
  # Hard failures (boot did NOT reach live userspace).
  if grep -aqE "Kernel panic - not syncing|Attempted to kill init|Give root password for maintenance|Cannot run /init" "$SERIAL"; then
    echo "FAIL:[$MODE] hard failure marker detected (panic/emergency)."
    grep -aE "Kernel panic|Attempted to kill init|Give root password for maintenance|Cannot run /init" "$SERIAL" | head -5 | sed 's/^/    /'
    fail=1
  fi
  # Success = a recognizable live-userspace milestone.
  if grep -aqE "login:|Welcome to|Adding live session user|Starting.*getty|Reached target.*Login|Reached target Multi-User|Reached target Graphical" "$SERIAL"; then
    echo "PASS:[$MODE] live userspace milestone reached."
  else
    if [[ $fail -eq 0 ]]; then
      echo "FAIL:[$MODE] no live-userspace milestone within ${TIMEOUT}s."
      echo "    --- last 15 serial lines ---"
      tail -15 "$SERIAL" | sed 's/^/    /'
    fi
    fail=1
  fi
else
  echo "FAIL:[$MODE] no serial output captured (boot may not have started)."
  fail=1
fi

echo "=== [$MODE] elapsed=${elapsed}s qemu_rc=$rc serial=$(wc -l <"$SERIAL" 2>/dev/null) lines ==="
exit $fail
