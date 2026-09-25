#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-jammy}"
ARCH="${REBUNTU_ARCH:-amd64}"
ROOTFS="${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-$SUITE-$ARCH}"
WORK="$ROOT/build/live"
ISO="$WORK/iso"
OUT="$ROOT/build/artifacts/images"
NAME="${REBUNTU_ISO_NAME:-rebuntu-$SUITE-$ARCH.iso}"

[[ -f "$ROOTFS/.rebuntu-rootfs" ]] || { echo "Build rootfs first: $ROOTFS" >&2; exit 1; }

for c in mksquashfs grub-mkstandalone xorriso mkfs.vfat mcopy; do
  command -v "$c" >/dev/null || { echo "Missing tool: $c" >&2; exit 1; }
done

sudo cp -L /etc/resolv.conf "$ROOTFS/etc/resolv.conf"
sudo chroot "$ROOTFS" apt-get update
sudo chroot "$ROOTFS" env DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  linux-image-generic initramfs-tools casper systemd-sysv dbus network-manager plymouth plymouth-themes plymouth-label
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

sudo mksquashfs "$ROOTFS" "$ISO/casper/filesystem.squashfs" \
  -comp xz -b 1M -noappend \
  -e boot dev proc sys run tmp var/cache/apt/archives

grub-mkstandalone \
  --format=i386-pc \
  --output="$WORK/core.img" \
  --install-modules="linux normal iso9660 biosdisk search search_fs_file search_label search_fs_uuid configfile echo ls cat test regexp gfxterm all_video video video_bochs video_cirrus font terminal part_msdos part_gpt" \
  --modules="linux normal iso9660 biosdisk search search_fs_file echo ls gfxterm all_video" \
  --locales="" --fonts="" \
  "boot/grub/grub.cfg=$ROOT/images/iso/config/grub.cfg"

cat /usr/lib/grub/i386-pc/cdboot.img "$WORK/core.img" > "$ISO/boot/grub/bios.img"

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

xorriso -as mkisofs \
  -r -V "REBUNTU" -o "$OUT/$NAME" -J -joliet-long -l \
  -b boot/grub/bios.img -c boot.catalog \
  -no-emul-boot -boot-load-size 4 -boot-info-table \
  --grub2-boot-info --grub2-mbr /usr/lib/grub/i386-pc/boot_hybrid.img \
  -eltorito-alt-boot -e EFI/efiboot.img -no-emul-boot \
  -isohybrid-gpt-basdat "$ISO"

sha256sum "$OUT/$NAME" > "$OUT/$NAME.sha256"
sudo chown "$(id -u):$(id -g)" "$OUT/$NAME" "$OUT/$NAME.sha256" 2>/dev/null || true
echo "Created:"
ls -lh "$OUT/$NAME" "$OUT/$NAME.sha256"
