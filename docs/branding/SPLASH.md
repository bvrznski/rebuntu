# Rebuntu Basic Splash

The boot splash is deliberately minimal:

- near-black background;
- static white Rebuntu mark;
- `R E B U N T U` wordmark;
- one thin cyan -> blue -> violet progress indicator;
- no percentage, spinner, loading label or decorative status text.

The progress indicator consumes Plymouth's actual boot-progress callback.

## Safety boundary

`bootstrap-rebuntu-splash.sh` only creates project files.

Installation, `update-alternatives`, `update-initramfs`, rootfs mutation and ISO
construction belong inside the isolated `rebuntu-builder` VM.

## Build path

```text
theme source
  -> rebuntu-plymouth-theme.deb
  -> target rootfs
  -> default.plymouth
  -> update-initramfs
  -> casper initrd
  -> live ISO
```

## Validation

Run source validation:

    ./tests/branding/test-plymouth-theme.sh

After building the rootfs inside the builder:

    REBUNTU_ROOTFS=/work/rootfs ./tests/branding/test-plymouth-rootfs.sh
