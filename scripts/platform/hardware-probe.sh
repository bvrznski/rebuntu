#!/usr/bin/env bash
set -Eeuo pipefail
g="$(lspci -nn 2>/dev/null|grep -Ei 'VGA|3D controller|Display controller'||true)"; p=cpu
grep -qi nvidia<<<"$g"&&p=nvidia
[[ $p == cpu ]]&&grep -Eqi 'AMD|ATI'<<<"$g"&&p=amd
[[ $p == cpu ]]&&grep -qi intel<<<"$g"&&p=intel
printf 'architecture=%s\nkernel=%s\naccelerator_provider=%s\n' "$(uname -m)" "$(uname -r)" "$p"
printf '%s\n' "$g"
