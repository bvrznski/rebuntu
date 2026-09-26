# Rebuntu Live Desktop Acceptance

Static tests do not prove a successful graphical boot.

Final acceptance requires:

- SeaBIOS boot
- OVMF/UEFI boot
- GRUB -> kernel/initramfs
- Plymouth
- GDM
- automatic Rebuntu live login
- Rebuntu GNOME Wayland session
- Xorg fallback
- NetworkManager
- working TTY
- clean shutdown/reboot

The passwordless sudo policy is live-image-only and must be removed
from the future installed-system path.
