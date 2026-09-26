#!/usr/bin/env bash
set -Eeuo pipefail
D="$(cd "$(dirname "${BASH_SOURCE[0]}")"&&pwd)"; R="$(cd "$D/../../.."&&pwd)"; mkdir -p "$R/build/artifacts/deb"
dpkg-deb --root-owner-group --build "$D" "$R/build/artifacts/deb/rebuntu-ai_0.1.0-1_all.deb"
