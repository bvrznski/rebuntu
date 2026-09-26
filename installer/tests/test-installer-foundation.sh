#!/usr/bin/env bash
set -Eeuo pipefail
R="${REBUNTU_ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/../.."&&pwd)}"
for f in installer/profiles/{base,desktop,ai,ai-dev}.conf installer/autoinstall/{user-data.example,meta-data}; do [[ -s "$R/$f" ]]||exit 1; echo "PASS $f"; done
grep -q REPLACE_ME "$R/installer/autoinstall/user-data.example"
