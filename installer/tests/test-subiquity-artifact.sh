#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CONF="$ROOT/installer/backend/subiquity/backend.conf"
ARTIFACTS="$ROOT/build/installer/subiquity"

source "$CONF"

SNAP="$ARTIFACTS/subiquity_${SUBIQUITY_REVISION}.snap"
ASSERT="$ARTIFACTS/subiquity_${SUBIQUITY_REVISION}.assert"

[[ -s "$SNAP" ]] || {
    echo "FAIL: missing $SNAP" >&2
    exit 1
}

[[ -s "$ASSERT" ]] || {
    echo "FAIL: missing $ASSERT" >&2
    exit 1
}

assert_revision="$(
    snap known snap-revision \
        snap-revision="$SUBIQUITY_REVISION" \
        2>/dev/null |
    awk '/^snap-revision:/ {print $2; exit}'
)"

[[ "$assert_revision" == "$SUBIQUITY_REVISION" ]] || {
    echo "FAIL: assertion for revision $SUBIQUITY_REVISION is not acknowledged" >&2
    exit 1
}

echo "PASS: Subiquity ${SUBIQUITY_VERSION} revision ${SUBIQUITY_REVISION}"
echo "PASS: snap artifact present"
echo "PASS: signed assertion acknowledged"
