# rebuntu-release

Development-safe Rebuntu identity package.

It installs `/etc/rebuntu-release` and `/etc/rebuntu-lsb-release`.
It deliberately does NOT overwrite the development host's `/etc/os-release`.

The image/rootfs builder will install the canonical Rebuntu `os-release`
when Rebuntu owns the target filesystem.
