#!/usr/bin/env bash
set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ART="$ROOT/build/artifacts/deb"
mkdir -p "$ART"

packages=(
  "$ROOT/packages/release/rebuntu-release"
  "$ROOT/packages/branding/rebuntu-branding"
  "$ROOT/packages/branding/rebuntu-plymouth-theme"
  "$ROOT/packages/live/rebuntu-live"
  "$ROOT/packages/meta/rebuntu-base"
)

for pkg in "${packages[@]}"; do
  echo "==> Building $(basename "$pkg")"
  (
    cd "$pkg"
    dpkg-buildpackage -us -uc -b
  )
done

find "$ROOT/packages" -maxdepth 3 -type f \
  \( -name '*.deb' -o -name '*.changes' -o -name '*.buildinfo' \) \
  -exec cp -f {} "$ART/" \;

echo
echo "Artifacts:"
find "$ART" -maxdepth 1 -type f -printf '  %f\n' | sort

# Rebuntu boot branding
"$ROOT/scripts/build/build-rebuntu-plymouth-theme.sh"
