#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CONF="$ROOT/installer/backend/subiquity/backend.conf"
OUT="$ROOT/build/installer/subiquity"

[[ -f "$CONF" ]] || {
    echo "ERROR: missing $CONF" >&2
    exit 1
}

# shellcheck source=/dev/null
source "$CONF"

mkdir -p "$OUT"
rm -f "$OUT"/subiquity_*.snap "$OUT"/subiquity_*.assert

echo "Fetching Subiquity ${SUBIQUITY_VERSION} rev ${SUBIQUITY_REVISION}..."
(
    cd "$OUT"
    snap download subiquity --channel="$SUBIQUITY_CHANNEL"
)

SNAP="$OUT/subiquity_${SUBIQUITY_REVISION}.snap"
ASSERT="$OUT/subiquity_${SUBIQUITY_REVISION}.assert"

[[ -s "$SNAP" ]] || {
    echo "ERROR: expected snap revision ${SUBIQUITY_REVISION} not downloaded" >&2
    exit 1
}

[[ -s "$ASSERT" ]] || {
    echo "ERROR: expected assertion revision ${SUBIQUITY_REVISION} not downloaded" >&2
    exit 1
}

echo "PASS: $SNAP"
echo "PASS: $ASSERT"
