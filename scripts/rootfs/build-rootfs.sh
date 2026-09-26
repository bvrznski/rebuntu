#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SUITE="${UBUNTU_SUITE:-jammy}"
ARCH="${REBUNTU_ARCH:-amd64}"
MIRROR="${UBUNTU_MIRROR:-http://archive.ubuntu.com/ubuntu}"
TARGET="${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-$SUITE-$ARCH}"
MANIFEST="$ROOT/distro/manifests/base/packages.list"
ART="$ROOT/build/artifacts/deb"

[[ "$TARGET" != "/" ]] || { echo "Refusing target /" >&2; exit 1; }
command -v debootstrap >/dev/null || { echo "Install debootstrap first." >&2; exit 1; }

if [[ ! -e "$TARGET/.rebuntu-rootfs" ]]; then
  if [[ -d "$TARGET" && -n "$(ls -A "$TARGET" 2>/dev/null)" ]]; then
    echo "Refusing non-empty unmarked target: $TARGET" >&2
    exit 1
  fi
  sudo mkdir -p "$TARGET"
  sudo debootstrap --arch="$ARCH" --variant=minbase "$SUITE" "$TARGET" "$MIRROR"
  sudo touch "$TARGET/.rebuntu-rootfs"
fi

# DNS for package installation.
sudo cp -L /etc/resolv.conf "$TARGET/etc/resolv.conf"

# Standard Ubuntu repositories for the selected base suite.
cat <<APT | sudo tee "$TARGET/etc/apt/sources.list" >/dev/null
deb $MIRROR $SUITE main restricted universe multiverse
deb $MIRROR $SUITE-updates main restricted universe multiverse
deb http://security.ubuntu.com/ubuntu $SUITE-security main restricted universe multiverse
APT

sudo chroot "$TARGET" apt-get update

mapfile -t pkgs < <(grep -Ev '^[[:space:]]*(#|$)' "$MANIFEST")
sudo chroot "$TARGET" env DEBIAN_FRONTEND=noninteractive \
  apt-get install -y --no-install-recommends "${pkgs[@]}"

# Install our locally built .debs. Install leaf packages first, metapackage last.
for name in rebuntu-release rebuntu-branding rebuntu-plymouth-theme rebuntu-live; do
  deb="$(find "$ART" -maxdepth 1 -type f -name "${name}_*.deb" | sort | tail -n1)"
  [[ -n "$deb" ]] || { echo "Missing $name .deb in $ART" >&2; exit 1; }
  sudo cp "$deb" "$TARGET/tmp/"
  sudo chroot "$TARGET" dpkg -i "/tmp/$(basename "$deb")" || \
    sudo chroot "$TARGET" apt-get -f install -y
done

base="$(find "$ART" -maxdepth 1 -type f -name 'rebuntu-base_*.deb' | sort | tail -n1)"
[[ -n "$base" ]] || { echo "Missing rebuntu-base .deb" >&2; exit 1; }
sudo cp "$base" "$TARGET/tmp/"
sudo chroot "$TARGET" dpkg -i "/tmp/$(basename "$base")" || \
  sudo chroot "$TARGET" apt-get -f install -y

# Now the target is owned by Rebuntu: canonical identity may replace Ubuntu identity.
sudo "$ROOT/scripts/install/apply-rebuntu-identity-to-rootfs.sh" "$TARGET"

printf 'rebuntu\n' | sudo tee "$TARGET/etc/hostname" >/dev/null
cat <<HOSTS | sudo tee "$TARGET/etc/hosts" >/dev/null
127.0.0.1 localhost
127.0.1.1 rebuntu
::1 localhost ip6-localhost ip6-loopback
HOSTS

# REBUNTU_PLATFORM_INTEGRATION_BEGIN
if [[ "${REBUNTU_INTEGRATE_PLATFORM:-0}" == "1" ]]; then
  sudo "$ROOT/scripts/rootfs/integrate-platform.sh" \
    "$TARGET" \
    "${REBUNTU_PROFILE:-desktop}"
fi
# REBUNTU_PLATFORM_INTEGRATION_END

sudo chroot "$TARGET" apt-get clean
sudo rm -f "$TARGET/tmp/"rebuntu-*.deb

echo "Built Rebuntu rootfs: $TARGET"


