#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
PKG="$ROOT/packages/branding/rebuntu-plymouth-theme"
PLY="$PKG/usr/share/plymouth/themes/rebuntu/rebuntu.plymouth"
SCRIPT="$PKG/usr/share/plymouth/themes/rebuntu/rebuntu.script"

test -s "$PLY"
test -s "$SCRIPT"
grep -q '^Name=Rebuntu$' "$PLY"
grep -q 'Plymouth.SetBootProgressFunction' "$SCRIPT"
grep -q 'R E B U N T U' "$SCRIPT"
! grep -qi 'loading' "$SCRIPT"
! grep -qi 'percent' "$SCRIPT"

echo "Rebuntu Plymouth source tests: PASS"
