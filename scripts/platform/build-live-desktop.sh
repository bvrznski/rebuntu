#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="${REBUNTU_ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)}"

SUITE="${UBUNTU_SUITE:-resolute}"
ARCH="${REBUNTU_ARCH:-amd64}"

ROOTFS="${REBUNTU_ROOTFS:-$ROOT/build/rootfs/rebuntu-$SUITE-$ARCH}"

cd "$ROOT"

echo "========================================"
echo " REBUNTU LIVE DESKTOP"
echo "========================================"
echo
echo "Repository: $ROOT"
echo "Rootfs:     $ROOTFS"
echo

echo "== Building platform packages =="

BUILDERS=(
    packages/meta/rebuntu-desktop/build.sh
    packages/meta/rebuntu-ai/build.sh
    packages/meta/rebuntu-ai-dev/build.sh
    packages/live/rebuntu-live-desktop/build.sh
)

for builder in "${BUILDERS[@]}"; do
    if [[ -x "$builder" ]]; then
        echo "-- $builder"
        "$builder"
    fi
done

echo
echo "== Building Rebuntu APT repository =="

"$ROOT/scripts/repository/build-repository.sh"

echo
echo "== Building desktop rootfs =="

REBUNTU_ROOTFS="$ROOTFS" \
REBUNTU_PROFILE=desktop \
REBUNTU_INTEGRATE_PLATFORM=1 \
    "$ROOT/scripts/rootfs/build-rootfs.sh"

echo
echo "== Testing rootfs =="

"$ROOT/tests/integration/test-live-desktop-rootfs.sh" \
    "$ROOTFS"

"$ROOT/tests/integration/test-embedded-repository.sh" \
    "$ROOTFS"

echo
echo "== Building ISO =="

"$ROOT/scripts/image/build-live-iso.sh"

echo
echo "== Testing ISO =="

"$ROOT/tests/integration/test-live-desktop-iso.sh"

echo
echo "========================================"
echo " REBUNTU LIVE DESKTOP BUILD COMPLETE"
echo "========================================"
echo
echo "ISO:"
echo "$ROOT/build/artifacts/images/rebuntu-resolute-amd64.iso"
echo
echo "Next stage: real SeaBIOS + OVMF boot."
