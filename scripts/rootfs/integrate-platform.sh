#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
TARGET="${1:?usage: integrate-platform.sh ROOTFS [profile]}"
PROFILE="${2:-${REBUNTU_PROFILE:-desktop}}"
REPO="$ROOT/repository"

[[ -f "$TARGET/.rebuntu-rootfs" ]] || {
    echo "ERROR: refusing unmarked rootfs: $TARGET" >&2
    exit 1
}

case "$PROFILE" in
    base)
        PROFILE_PACKAGE="rebuntu-base"
        ;;
    desktop)
        PROFILE_PACKAGE="rebuntu-live-desktop"
        ;;
    ai)
        PROFILE_PACKAGE="rebuntu-ai"
        ;;
    ai-dev)
        PROFILE_PACKAGE="rebuntu-ai-dev"
        ;;
    *)
        echo "ERROR: unknown profile: $PROFILE" >&2
        exit 2
        ;;
esac

echo "== Rebuntu platform integration =="
echo "rootfs:  $TARGET"
echo "profile: $PROFILE"
echo "package: $PROFILE_PACKAGE"

# Embedded APT repository.
# trusted=yes applies ONLY to the image-local file:// repository.
sudo rm -rf "$TARGET/opt/rebuntu/repository"
sudo mkdir -p "$TARGET/opt/rebuntu"

sudo cp -a \
    "$REPO" \
    "$TARGET/opt/rebuntu/repository"

sudo mkdir -p "$TARGET/etc/apt/sources.list.d"

cat <<APT | sudo tee \
    "$TARGET/etc/apt/sources.list.d/rebuntu-local.list" >/dev/null
deb [trusted=yes] file:/opt/rebuntu/repository resolute main
APT

# ------------------------------------------------------------
# Chroot mounts
# ------------------------------------------------------------

MOUNTS=()

cleanup() {
    local i

    for ((i=${#MOUNTS[@]}-1; i>=0; i--)); do
        sudo umount -lf "${MOUNTS[$i]}" 2>/dev/null || true
    done
}

trap cleanup EXIT

bind_mount() {
    local src="$1"
    local dst="$2"

    sudo mkdir -p "$dst"

    if ! mountpoint -q "$dst"; then
        sudo mount --bind "$src" "$dst"
        MOUNTS+=("$dst")
    fi
}

virtual_mount() {
    local type="$1"
    local source="$2"
    local dst="$3"

    sudo mkdir -p "$dst"

    if ! mountpoint -q "$dst"; then
        sudo mount -t "$type" "$source" "$dst"
        MOUNTS+=("$dst")
    fi
}

bind_mount /dev "$TARGET/dev"
bind_mount /dev/pts "$TARGET/dev/pts"

virtual_mount proc proc "$TARGET/proc"
virtual_mount sysfs sysfs "$TARGET/sys"

bind_mount /run "$TARGET/run"


# ------------------------------------------------------------
# Install selected Rebuntu profile
# ------------------------------------------------------------

sudo chroot "$TARGET" apt-get update

sudo chroot "$TARGET" \
    env DEBIAN_FRONTEND=noninteractive \
    apt-get install -y "$PROFILE_PACKAGE"

# ------------------------------------------------------------
# Live desktop
# ------------------------------------------------------------

if [[ "$PROFILE" != "base" ]]; then

    if ! sudo chroot "$TARGET" id rebuntu >/dev/null 2>&1; then
        sudo chroot "$TARGET" useradd \
            --create-home \
            --shell /bin/bash \
            --comment "Rebuntu Live User" \
            rebuntu
    fi

    # Add only groups actually existing in the target.
    GROUPS=()

    for group in \
        sudo \
        audio \
        video \
        plugdev \
        netdev \
        render
    do
        if sudo chroot "$TARGET" \
            getent group "$group" >/dev/null 2>&1
        then
            GROUPS+=("$group")
        fi
    done

    if ((${#GROUPS[@]})); then
        GROUP_CSV="$(IFS=,; echo "${GROUPS[*]}")"

        sudo chroot "$TARGET" \
            usermod -aG "$GROUP_CSV" rebuntu
    fi

    # Live user password; GDM autologin remains enabled separately.
    echo "rebuntu:rebuntu" | sudo chroot "$TARGET" chpasswd

    # Keep Casper live identity consistent with Rebuntu.
    if [[ -f "$TARGET/etc/casper.conf" ]]; then
        sudo sed -i 's/^export USERNAME=.*/export USERNAME="rebuntu"/; s/^export HOST=.*/export HOST="rebuntu"/' "$TARGET/etc/casper.conf"
    fi

    # LIVE IMAGE ONLY.
    # Installer must remove this from an installed system.
    sudo mkdir -p "$TARGET/etc/sudoers.d"

    echo 'rebuntu ALL=(ALL) NOPASSWD:ALL' |
        sudo tee \
            "$TARGET/etc/sudoers.d/90-rebuntu-live" \
            >/dev/null

    sudo chmod 0440 \
        "$TARGET/etc/sudoers.d/90-rebuntu-live"

    # AccountsService session selection.
    sudo mkdir -p \
        "$TARGET/var/lib/AccountsService/users"

    cat <<ACCOUNT |
        sudo tee \
            "$TARGET/var/lib/AccountsService/users/rebuntu" \
            >/dev/null
[User]
Session=rebuntu
XSession=rebuntu
SystemAccount=false
ACCOUNT

    # Configure GDM for the Rebuntu live session without replacing the
    # distribution-owned /etc/gdm3/custom.conf.
    sudo mkdir -p "$TARGET/etc/gdm3"

    sudo python3 - "$TARGET/etc/gdm3/custom.conf" <<'GDM_PY'
import sys
from pathlib import Path

path = Path(sys.argv[1])
text = path.read_text() if path.exists() else ""

if "[daemon]" not in text:
    text += "\n[daemon]\n"

lines = text.splitlines()
out = []
in_daemon = False
seen = set()

settings = {
    "AutomaticLoginEnable": "true",
    "AutomaticLogin": "rebuntu",
    "WaylandEnable": "true",
}

for line in lines:
    stripped = line.strip()

    if stripped.startswith("[") and stripped.endswith("]"):
        if in_daemon:
            for key, value in settings.items():
                if key not in seen:
                    out.append(f"{key}={value}")
        in_daemon = stripped == "[daemon]"
        seen = set()
        out.append(line)
        continue

    if in_daemon and "=" in stripped and not stripped.startswith("#"):
        key = stripped.split("=", 1)[0].strip()
        if key in settings:
            if key not in seen:
                out.append(f"{key}={settings[key]}")
                seen.add(key)
            continue

    out.append(line)

if in_daemon:
    for key, value in settings.items():
        if key not in seen:
            out.append(f"{key}={value}")

path.write_text("\n".join(out).rstrip() + "\n")
GDM_PY

    # Rebuntu: let NetworkManager manage Ethernet and other device types.
    sudo mkdir -p "$TARGET/etc/NetworkManager/conf.d"
    printf '[keyfile]\nunmanaged-devices=\n' | sudo tee "$TARGET/etc/NetworkManager/conf.d/90-rebuntu-managed-devices.conf" >/dev/null


# Optional Rebuntu installer layer for Live images only.
if [[ "${REBUNTU_INSTALLER:-0}" == "1" ]]; then
    INSTALLER_ARTIFACTS="$ROOT/build/installer/subiquity"
    INSTALLER_TARGET="$TARGET/opt/rebuntu/installer/subiquity"

    sudo chroot "$TARGET" apt-get install -y snapd

    SNAP="$(find "$INSTALLER_ARTIFACTS" -maxdepth 1 -type f -name 'subiquity_*.snap' -print -quit)"
    ASSERT="$(find "$INSTALLER_ARTIFACTS" -maxdepth 1 -type f -name 'subiquity_*.assert' -print -quit)"

    [[ -n "$SNAP" && -s "$SNAP" ]] || {
        echo "ERROR: Subiquity snap artifact missing" >&2
        exit 1
    }
    [[ -n "$ASSERT" && -s "$ASSERT" ]] || {
        echo "ERROR: Subiquity assertion artifact missing" >&2
        exit 1
    }

    sudo mkdir -p "$INSTALLER_TARGET"
    sudo install -m 0644 "$SNAP" "$INSTALLER_TARGET/"
    sudo install -m 0644 "$ASSERT" "$INSTALLER_TARGET/"
fi

    sudo chroot "$TARGET" \
        systemctl set-default graphical.target
    sudo chroot "$TARGET" \
        systemctl enable gdm3.service

    sudo chroot "$TARGET" \
        systemctl enable NetworkManager.service

    sudo chroot "$TARGET" \
        systemctl enable ssh.service
fi

# Let booted system generate its own machine-id.
sudo truncate -s 0 "$TARGET/etc/machine-id"
sudo rm -f "$TARGET/var/lib/dbus/machine-id"

sudo chroot "$TARGET" apt-get clean

echo
echo "Rebuntu platform integration complete."
