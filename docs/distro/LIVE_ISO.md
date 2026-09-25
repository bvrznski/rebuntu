# Rebuntu Live ISO

Pipeline:

    validated Rebuntu rootfs
        -> upstream Ubuntu generic Linux kernel
        -> initramfs + casper
        -> SquashFS
        -> GRUB BIOS/UEFI
        -> hybrid ISO

This is intentionally the first minimal bootable live milestone. It does not
replace Linux and does not yet introduce a custom kernel flavour. Desktop,
installer, signing and release hardening remain later stages.
