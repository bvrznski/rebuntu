#!/usr/bin/env bash
set -Eeuo pipefail
pkg="${1:?usage: build-deb.sh PACKAGE_DIRECTORY}"
pkg="$(realpath "$pkg")"
[[ -f "$pkg/debian/control" ]] || { echo "No debian/control in $pkg" >&2; exit 1; }
cd "$pkg"
dpkg-buildpackage -us -uc -b
