# Rebuntu Distribution Architecture

    Debian
      |
    Ubuntu
      |
    Rebuntu
      +-- distro/       distribution identity/defaults/policy
      +-- packages/     Debian packages and metapackages
      +-- repository/   APT archive
      +-- images/       ISO/live/VM/recovery images
      +-- installer/    installation layer
      +-- branding/     canonical visual/terminal assets
      +-- desktop/      Rebuntu desktop/graphics track
      +-- kernel/       Linux configuration/flavour/limited patches
      +-- hardware/     hardware enablement
      +-- system/       native system integration
      +-- src/          existing Rebuntu runtime/platform

`src/` remains independently owned by the active implementation track.

Rebuntu inherits upstream mechanisms by default. Linux, systemd, udev,
APT/dpkg, Wayland, Mesa/NVIDIA and other native mechanisms remain authoritative.
