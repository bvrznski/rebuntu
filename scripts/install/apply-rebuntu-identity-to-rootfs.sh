#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
TARGET="${1:?usage: apply-rebuntu-identity-to-rootfs.sh /path/to/rootfs}"

[[ "$TARGET" != "/" ]] || { echo "Refusing to modify host root filesystem." >&2; exit 1; }
[[ -d "$TARGET/etc" ]] || { echo "Target does not look like a rootfs: $TARGET" >&2; exit 1; }

install -Dm0644 "$ROOT/distro/identity/os-release" "$TARGET/usr/lib/os-release"
ln -sfn ../usr/lib/os-release "$TARGET/etc/os-release"
install -Dm0644 "$ROOT/distro/identity/rebuntu-release" "$TARGET/etc/rebuntu-release"
install -Dm0644 "$ROOT/distro/identity/lsb-release" "$TARGET/etc/lsb-release"

echo "Applied Rebuntu identity to $TARGET"
