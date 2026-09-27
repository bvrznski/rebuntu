#!/usr/bin/env bash
set -Eeuo pipefail

# Source diagnostics - record revision info for traceability
GIT_SHA=$(git rev-parse HEAD 2>/dev/null || echo "UNKNOWN")
GIT_DIRTY=$(git diff --quiet 2>/dev/null && echo "clean" || echo "dirty")

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-resolute}"
ARCH="${REBUNTU_ARCH:-amd64}"
ROOTFS="${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-$SUITE-$ARCH}"
WORK="$ROOT/build/live"
ISO="$WORK/iso"
OUT="$ROOT/build/artifacts/images"
NAME="${REBUNTU_ISO_NAME:-rebuntu-$SUITE-$ARCH.iso}"

echo "=== Rebuntu ISO Build ==="
echo "Git revision: $GIT_SHA ($GIT_DIRTY)"
echo "Suite: $SUITE, Arch: $ARCH"
echo "Output directory: $OUT"

[[ -f "$ROOTFS/.rebuntu-rootfs" ]] || { echo "FAIL: Build rootfs first: $ROOTFS" >&2; exit 1; }

for c in mksquashfs grub-mkstandalone xorriso mkfs.vfat mcopy; do
  command -v "$c" >/dev/null || { echo "Missing tool: $c" >&2; exit 1; }
done

# Casper requires the live root to contain the /dev, /proc, /sys, /run and /tmp
# mount-point directories so it can bind the live system's kernel interfaces into
# the mounted SquashFS. Excluding them (as the previous build did) makes casper's
# init-bottom step fail with "mount: mounting /dev on /root/dev failed" and the
# boot panics before userspace. We therefore keep those (empty) directories in the
# SquashFS and only exclude the kernel/initrd (shipped separately under /casper)
# and regenerable APT caches.
sudo cp -L /etc/resolv.conf "$ROOTFS/etc/resolv.conf"
sudo chroot "$ROOTFS" apt-get update
sudo chroot "$ROOTFS" env DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  linux-image-generic initramfs-tools casper systemd-sysv dbus network-manager plymouth plymouth-themes plymouth-label

# Ensure the live mount-point directories exist before packing (they are empty and
# negligible in size). This is the authoritative requirement for a working casper
# live boot.
sudo mkdir -p "$ROOTFS/dev" "$ROOTFS/proc" "$ROOTFS/sys" "$ROOTFS/run" "$ROOTFS/tmp"
sudo chmod 1777 "$ROOTFS/tmp" "$ROOTFS/dev" 2>/dev/null || true

# Plymouth requires the framebuffer initramfs hook.
sudo mkdir -p "$ROOTFS/etc/initramfs-tools/conf.d"
echo 'FRAMEBUFFER=y' | \
    sudo tee "$ROOTFS/etc/initramfs-tools/conf.d/rebuntu-plymouth" >/dev/null
sudo chroot "$ROOTFS" update-initramfs -u -k all

KERNEL="$(find "$ROOTFS/boot" -maxdepth 1 -type f -name 'vmlinuz-*' | sort -V | tail -n1)"
[[ -n "$KERNEL" ]] || { echo "No kernel in rootfs." >&2; exit 1; }
KVER="${KERNEL##*/vmlinuz-}"
INITRD="$ROOTFS/boot/initrd.img-$KVER"
[[ -f "$INITRD" ]] || { echo "Missing $INITRD" >&2; exit 1; }

# Rebuntu Plymouth must be embedded in the final initramfs.
sudo lsinitramfs "$INITRD" \
  | grep -q "usr/share/plymouth/themes/rebuntu/rebuntu.script" \
  || {
    echo "ERROR: Rebuntu Plymouth theme missing from initramfs." >&2
    exit 1
  }

sudo rm -rf "$WORK"
mkdir -p "$ISO/casper" "$ISO/boot/grub" "$ISO/EFI/BOOT" "$OUT"

sudo install -m 0644 "$KERNEL" "$ISO/casper/vmlinuz"
sudo install -m 0644 "$INITRD" "$ISO/casper/initrd"
cp "$ROOT/images/iso/config/grub.cfg" "$ISO/boot/grub/grub.cfg"

sudo chroot "$ROOTFS" dpkg-query -W --showformat='${Package} ${Version}\n' \
  | sudo tee "$ISO/casper/filesystem.manifest" >/dev/null
printf '%s\n' "$(sudo du -sx --block-size=1 "$ROOTFS" | cut -f1)" \
  | sudo tee "$ISO/casper/filesystem.size" >/dev/null

# Keep /dev /proc /sys /run /tmp (casper live-boot mount points) INSIDE the
# SquashFS. Exclude only the separately-shipped kernel/initrd tree and regenerable
# APT state.
sudo mksquashfs "$ROOTFS" "$ISO/casper/filesystem.squashfs" \
  -comp xz -b 1M -noappend \
  -e boot var/cache/apt/archives var/lib/apt/lists

# BIOS GRUB (i386-pc) El Torito image
# Build core.img explicitly, then prepend GRUB's CD-ROM bootstrap.
# This gives BIOS GRUB direct access to the El Torito CD device and ISO9660.
grub-mkstandalone \
  --format=i386-pc \
  --output="$WORK/core.img" \
  --install-modules="biosdisk iso9660 normal linux search search_fs_file configfile echo ls cat test regexp all_video gfxterm" \
  --modules="biosdisk iso9660 normal linux search search_fs_file configfile echo ls cat test regexp" \
  --locales="" \
  --fonts="" \
  "boot/grub/grub.cfg=$ROOT/images/iso/config/grub.cfg"

cat /usr/lib/grub/i386-pc/cdboot.img "$WORK/core.img" \
  > "$ISO/boot/grub/bios.img"

[[ -s "$ISO/boot/grub/bios.img" ]] || {
  echo "ERROR: BIOS El Torito image is empty." >&2
  exit 1
}

# UEFI GRUB (x86_64-efi) standalone image
grub-mkstandalone \
  --format=x86_64-efi \
  --output="$ISO/EFI/BOOT/BOOTX64.EFI" \
  --locales="" --fonts="" \
  "boot/grub/grub.cfg=$ROOT/images/iso/config/grub.cfg"

dd if=/dev/zero of="$WORK/efiboot.img" bs=1M count=8 status=none
mkfs.vfat "$WORK/efiboot.img" >/dev/null
mmd -i "$WORK/efiboot.img" ::EFI ::EFI/BOOT
mcopy -i "$WORK/efiboot.img" "$ISO/EFI/BOOT/BOOTX64.EFI" ::EFI/BOOT/
cp "$WORK/efiboot.img" "$ISO/EFI/efiboot.img"

# The i386-pc-eltorito format creates a standalone image that includes the
# El Torito boot sector and all necessary modules, so we reference it directly.
xorriso -as mkisofs \
  -r -V "REBUNTU" -o "$OUT/$NAME" -J -joliet-long -l \
  -b boot/grub/bios.img -c boot.catalog \
  -no-emul-boot -boot-load-size 4 -boot-info-table \
  --grub2-boot-info \
  -eltorito-alt-boot -e EFI/efiboot.img -no-emul-boot \
  -isohybrid-gpt-basdat "$ISO"

sha256sum "$OUT/$NAME" > "$OUT/$NAME.sha256"
sudo chown "$(id -u):$(id -g)" "$OUT/$NAME" "$OUT/$NAME.sha256" 2>/dev/null || true

# Output comprehensive diagnostics
ISO_SIZE=$(stat -c%s "$OUT/$NAME")
SHA256_HASH=$(sha256sum "$OUT/$NAME" | cut -d' ' -f1)

echo ""
echo "=== Build Complete ==="
echo "ISO path: $OUT/$NAME"
echo "ISO size: $ISO_SIZE bytes ($(numfmt --to=iec $ISO_SIZE))"
echo "SHA256: $SHA256_HASH"
echo "Git revision: $GIT_SHA ($GIT_DIRTY)"

# Verify critical files exist in the final ISO
echo ""
echo "=== Verification ==="
VERIFIED=true

xorriso -indev "$OUT/$NAME" -find /casper/vmlinuz 2>/dev/null | grep -q vmlinuz && \
  echo "PASS: /casper/vmlinuz present" || { echo "FAIL: /casper/vmlinuz missing"; VERIFIED=false; }

xorriso -indev "$OUT/$NAME" -find /casper/initrd 2>/dev/null | grep -q initrd && \
  echo "PASS: /casper/initrd present" || { echo "FAIL: /casper/initrd missing"; VERIFIED=false; }

xorriso -indev "$OUT/$NAME" -find /casper/filesystem.squashfs 2>/dev/null | grep -q squashfs && \
  echo "PASS: /casper/filesystem.squashfs present" || { echo "FAIL: /casper/filesystem.squashfs missing"; VERIFIED=false; }

xorriso -indev "$OUT/$NAME" -find /boot/grub/grub.cfg 2>/dev/null | grep -q grub.cfg && \
  echo "PASS: /boot/grub/grub.cfg present" || { echo "FAIL: /boot/grub/grub.cfg missing"; VERIFIED=false; }

xorriso -indev "$OUT/$NAME" -find /EFI/BOOT/BOOTX64.EFI 2>/dev/null | grep -q BOOTX64 && \
  echo "PASS: /EFI/BOOT/BOOTX64.EFI present" || { echo "FAIL: /EFI/BOOT/BOOTX64.EFI missing"; VERIFIED=false; }

if [[ "$VERIFIED" == "true" ]]; then
  echo "=== All verifications passed ==="
else
  echo "=== Some verifications failed - check output above ==="
  exit 1
fi