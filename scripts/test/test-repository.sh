#!/usr/bin/env bash
set -Eeuo pipefail
R="${REBUNTU_ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/../.."&&pwd)}"; X="$R/repository"; P="$X/dists/jammy/main/binary-amd64/Packages"; bad=0
for f in "$P" "$P.gz" "$P.xz" "$X/dists/jammy/Release"; do [[ -s $f ]]&&echo "PASS $f"||{ echo "FAIL $f";bad=1;}; done
grep -q '^Package: rebuntu-base$' "$P"||{ echo "FAIL rebuntu-base index";bad=1; }
while read -r f; do [[ -f "$X/$f" ]]||{ echo "FAIL missing $f";bad=1;}; done < <(awk '/^Filename:/{print $2}' "$P")
((bad==0))
