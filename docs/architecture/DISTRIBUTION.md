# Rebuntu Distribution Architecture

High-level ownership:

    Debian
      |
    Ubuntu
      |
    Rebuntu distribution layer
      |
      +-- distro/
      +-- packages/
      +-- repository/
      +-- images/
      +-- installer/
      +-- branding/
      +-- desktop/
      +-- kernel/
      +-- hardware/
      +-- system/
      +-- release/
      |
      +-- src/        Rebuntu runtime/platform
      |
      +-- tests/
      +-- tools/
      +-- docs/

The distribution layer surrounds and packages the runtime.

It must not duplicate Linux mechanisms already provided by the kernel,
systemd, udev, package management, graphics stack or other authoritative
upstream components.
