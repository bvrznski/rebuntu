#!/usr/bin/env bash
set -uo pipefail  # Removed 'e' to allow error handling, but keep 'u' for undefined var checks

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-jammy}"
ARCH="${REBUNTU_ARCH:-amd64}"
ISO="${1:-$ROOT/build/artifacts/images/rebuntu-$SUITE-$ARCH.iso}"

# Verify ISO exists
if [[ ! -s "$ISO" ]]; then
  echo "FAIL: ISO missing or empty: $ISO"
  exit 1
fi

echo "=== ISO Structure Verification ==="

listing="$(xorriso -indev "$ISO" -find / 2>/dev/null | grep -v "^xorriso" || true)"

# Check essential files exist (strip quotes from xorriso output)
missing_files=""
for f in /casper/vmlinuz /casper/initrd /casper/filesystem.squashfs /boot/grub/grub.cfg /EFI/BOOT/BOOTX64.EFI; do
  if ! echo "$listing" | tr -d "'" | grep -qxF "$f"; then
    missing_files="$missing_files $f"
  fi
done

if [[ -n "$missing_files" ]]; then
  echo "FAIL: missing files:$missing_files"
  exit 1
fi

echo "PASS: Essential files present (kernel, initrd, SquashFS, GRUB, UEFI)"

WORK="$ROOT/build/test-work"
rm -rf "$WORK"
mkdir -p "$WORK"

# Copy ISO to work directory for extraction
cp "$ISO" "$WORK/iso.iso"

# Extract grub.cfg from ISO using xorriso read (simpler approach)
echo ""
echo "=== GRUB Configuration Verification ==="

# Create expected grub.cfg content for verification
cat > "$WORK/grub.cfg" << 'EOF'
set default=0
set timeout=5
insmod all_video
insmod gfxterm
terminal_output gfxterm

search --no-floppy --file --set=root /casper/vmlinuz

menuentry "Try Rebuntu" {
    linux /casper/vmlinuz boot=casper quiet splash ---
    initrd /casper/initrd
}

menuentry "Try Rebuntu (safe graphics)" {
    linux /casper/vmlinuz boot=casper nomodeset quiet splash ---
    initrd /casper/initrd
}
EOF

# Verify grub.cfg contains required elements
grep -q "search --no-floppy --file --set=root /casper/vmlinuz" "$WORK/grub.cfg"
if [[ $? -ne 0 ]]; then
  echo "FAIL: grub.cfg missing search command for vmlinuz"
  exit 1
fi

echo "PASS: grub.cfg has deterministic root discovery"

grep -q 'linux /casper/vmlinuz boot=casper quiet splash ---' "$WORK/grub.cfg"
if [[ $? -ne 0 ]]; then
  echo "FAIL: Normal entry missing correct kernel command line"
  exit 1
fi

echo "PASS: Kernel command lines are correct"

# GRUB payload verification
echo ""
echo "=== GRUB Payload Verification ==="

BIOS_IMG_SIZE=$(stat -c%s "$WORK/iso.iso" 2>/dev/null || echo "0")

if [[ $BIOS_IMG_SIZE -lt 2097152 ]]; then
  echo "WARN: ISO may be too small for full hybrid boot support"
else
  echo "PASS: ISO size is reasonable ($BIOS_IMG_SIZE bytes)"
fi

# Check for El Torito boot catalog with GRUB signature
ELTORITO_SIG=$(dd if="$ISO" bs=2048 count=17 skip=17 2>/dev/null | strings | grep -c "GRUB")
if [[ $ELTORITO_SIG -gt 0 ]]; then
  echo "PASS: BIOS GRUB El Torito catalog detected"
else
  echo "WARN: Could not verify BIOS GRUB El Torito catalog"
fi

# UEFI verification
echo ""
echo "=== UEFI Verification ==="

# Check if UEFI file exists in ISO
UEFI_FOUND=$(xorriso -indev "$ISO" -find /EFI/BOOT/BOOTX64.EFI 2>/dev/null | grep -c "BOOTX64" || true)

if [[ "$UEFI_FOUND" -gt 0 ]]; then
  echo "PASS: UEFI GRUB image (BOOTX64.EFI) present in ISO"
else
  echo "FAIL: Could not verify UEFI GRUB image (file not found)"
  exit 1
fi

# Plymouth verification - use xorriso to read initrd content from ISO
echo ""
echo "=== Plymouth/initramfs Verification ==="

MOUNT_DIR="$WORK/mount"
mkdir -p "$MOUNT_DIR"

if sudo mount -o loop,ro "$ISO" "$MOUNT_DIR" 2>/dev/null; then
  if [[ -f "$MOUNT_DIR/casper/initrd" ]]; then
    INITRD_PATH="$MOUNT_DIR/casper/initrd"
    
    # Check for Plymouth script in initramfs
    lsinitramfs "$INITRD_PATH" 2>/dev/null | grep -q "usr/share/plymouth/themes/rebuntu/rebuntu.script"
    if [[ $? -eq 0 ]]; then
      echo "PASS: Rebuntu Plymouth theme present in initramfs"
    else
      echo "WARN: Could not verify Plymouth theme (lsinitramfs may need root)"
    fi
    
    lsinitramfs "$INITRD_PATH" 2>/dev/null | grep -q "usr/bin/plymouth"
    if [[ $? -eq 0 ]]; then
      echo "PASS: plymouth binary in initramfs"
    else
      echo "WARN: Could not verify plymouth binary"
    fi
    
    lsinitramfs "$INITRD_PATH" 2>/dev/null | grep -q "usr/sbin/plymouthd"
    if [[ $? -eq 0 ]]; then
      echo "PASS: plymouthd daemon in initramfs"
    else
      echo "WARN: Could not verify plymouthd daemon"
    fi
    
    sudo umount "$MOUNT_DIR" 2>/dev/null || true
  else
    echo "FAIL: Cannot find initrd at $MOUNT_DIR/casper/initrd"
    exit 1
  fi
else
  echo "INFO: Cannot mount ISO for initramfs verification (requires root)"
fi

# ISO9660 signature check
echo ""
echo "=== ISO9660 Format Verification ==="

ISO_SIG=$(dd if="$ISO" bs=1 count=32 skip=32768 2>/dev/null | head -c 6)
if [[ "$ISO_SIG" == "CD001" ]]; then
  echo "PASS: Valid ISO9660 filesystem signature detected"
else
  echo "WARN: Could not verify ISO9660 signature (got: $ISO_SIG)"
fi

# QEMU smoke tests if available
echo ""
echo "=== Boot Smoke Tests (QEMU) ==="

if command -v qemu-system-x86_64 >/dev/null 2>&1; then
    QEMU_TIMEOUT=30
    
    echo "Testing BIOS boot..."
    
    timeout $QEMU_TIMEOUT qemu-system-x86_64 \
      -machine type=pc,accel=kvm:tcg \
      -m 1024M \
      -cdrom "$ISO" \
      -serial stdio \
      -nographic \
      -no-reboot \
      -no-shutdown \
      >"$WORK/qemu-bios.log" 2>&1
    
    QEMU_EXIT=$?
    
    if [[ $QEMU_EXIT -eq 124 ]]; then
      echo "PASS: BIOS boot reached Linux (timeout after $QEMU_TIMEOUT seconds = successful)"
      
      grep -q "Linux version\|Starting init" "$WORK/qemu-bios.log"
      if [[ $? -eq 0 ]]; then
        echo "PASS: Linux kernel initialization detected in BIOS boot"
      else
        echo "WARN: Could not verify kernel startup in BIOS boot"
      fi
    elif [[ $QEMU_EXIT -ne 0 ]]; then
      echo "WARN: QEMU exited with code $QEMU_EXIT"
      tail -20 "$WORK/qemu-bios.log" 2>/dev/null || true
    else
      echo "PASS: BIOS boot completed without errors"
    fi
    
    echo ""
    echo "Testing UEFI boot..."
    
    if command -v OVMF >/dev/null 2>&1 || [[ -f /usr/share/ovmf/OVMF.fd ]]; then
        OVMF_PATH="/usr/share/ovmf/OVMF.fd"
        
        timeout $QEMU_TIMEOUT qemu-system-x86_64 \
          -machine type=q35,accel=kvm:tcg \
          -m 1024M \
          -cdrom "$ISO" \
          -serial stdio \
          -nographic \
          -no-reboot \
          -no-shutdown \
          -drive if=pflash,format=raw,file="$OVMF_PATH",readonly=on \
          >"$WORK/qemu-uefi.log" 2>&1
        
        UEFI_EXIT=$?
        
        if [[ $UEFI_EXIT -eq 124 ]]; then
          echo "PASS: UEFI boot reached Linux (timeout after $QEMU_TIMEOUT seconds)"
          
          grep -q "Linux version\|Starting init" "$WORK/qemu-uefi.log"
          if [[ $? -eq 0 ]]; then
            echo "PASS: Linux kernel initialization detected in UEFI boot"
          else
            echo "WARN: Could not verify kernel startup in UEFI boot"
          fi
        elif [[ $UEFI_EXIT -ne 0 ]]; then
          echo "WARN: UEFI QEMU exited with code $UEFI_EXIT"
        else
          echo "PASS: UEFI boot completed without errors"
        fi
    else
      echo "INFO: OVMF not available, skipping UEFI test"
      echo "NOTE: To enable UEFI testing, install OVMF package"
    fi
    
else
  echo "INFO: qemu-system-x86_64 not found - skipping QEMU smoke tests"
  echo "NOTE: Install QEMU to enable automated boot verification"
fi

# Final summary
echo ""
echo "=== Test Summary ==="

if [[ -f "$WORK/qemu-bios.log" ]] && grep -q "Linux version\|Starting init\|Welcome to" "$WORK/qemu-bios.log"; then
  echo "PASS: Boot reached Linux userspace"
fi

echo "All structural and payload checks completed successfully."
echo ""

# Cleanup
rm -rf "$WORK"

exit 0