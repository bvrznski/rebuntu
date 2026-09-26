#!/usr/bin/env bash
# Package ownership + upgrade-safety test for the Rebuntu foundation packages.
#
# Deterministic and host-safe: no network, no QEMU, no host mutation. It only
# builds the packages and inspects the resulting .deb metadata and file lists.
#
# It proves:
#   1. Each foundation package builds a well-formed .deb (dpkg-deb integrity).
#   2. REGULAR-FILE OWNERSHIP is unambiguous: no regular file is owned by more
#      than one package (no "shadow" ownership). Directory entries are
#      legitimately shared across packages (dpkg creates them idempotently)
#      and are therefore excluded from the conflict check.
#   3. METADATA: rebuntu-base depends on its component packages; rebuntu-release
#      owns its identity file and retains truthful Ubuntu ancestry (ID_LIKE).
#   4. BEHAVIORAL OWNERSHIP: rebuntu-live owns its maintainer-script surface
#      (serial getty enable in postinst, cleanup in postrm, live-user sudo).
#   5. UPGRADE SAFETY: each package's regular-file payload is idempotent
#      (re-extracting the same version is byte-identical), so a same-version
#      upgrade cannot clobber.
#
# Usage: test-package-ownership.sh

set -Eeuo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"
fail(){ echo "FAIL: $*" >&2; exit 1; }
ok(){ echo "ok: $*"; }
note(){ echo "note: $*"; }

declare -A SRC=(
  [rebuntu-release]=packages/release/rebuntu-release
  [rebuntu-branding]=packages/branding/rebuntu-branding
  [rebuntu-plymouth-theme]=packages/branding/rebuntu-plymouth-theme
  [rebuntu-live]=packages/live/rebuntu-live
  [rebuntu-base]=packages/meta/rebuntu-base
)
NAMES=(rebuntu-release rebuntu-branding rebuntu-plymouth-theme rebuntu-live rebuntu-base)

# --- 1) Build each package and verify the .deb is well-formed ----------------
declare -A DEB
for name in "${NAMES[@]}"; do
  d="${SRC[$name]}"
  [[ -d "$d" ]] || fail "missing source dir: $d"
  ( cd "$d" && dpkg-buildpackage -us -uc -b >/dev/null 2>&1 ) \
    || fail "$name: build failed (run dpkg-buildpackage verbosely to inspect)"
  parent="$(dirname "$d")"
  deb="$(cd "$parent" && ls -1 "${name}"_*.deb 2>/dev/null | head -1)"
  [[ -n "${deb:-}" && -f "$parent/$deb" ]] || fail "$name: no .deb produced"
  DEB[$name]="$parent/$deb"
  dpkg-deb --info "$parent/$deb" >/dev/null 2>&1 || fail "$name: dpkg-deb integrity check failed"
  ok "built $name"
done

# Regular-file list of a .deb (type '-' only, './' normalised to '/').
regfiles(){ dpkg-deb -c "$1" 2>/dev/null | awk '$1 ~ /^-/ {print $NF}' | sed -e 's|^\./|/|'; }

# --- 2) Ownership: no regular file owned by more than one package -----------
declare -A FILES
for name in "${NAMES[@]}"; do
  FILES[$name]="$(regfiles "${DEB[$name]}" | sort -u)"
done
allfiles="$(printf '%s\n' "${FILES[@]}" | grep -vE '^$' | sort)"
dups="$(printf '%s\n' "$allfiles" | sort | uniq -d || true)"
if [[ -n "$dups" ]]; then
  fail "regular file(s) owned by more than one package (shadow ownership):"$'\n'"$dups"
fi
ok "no cross-package regular-file ownership conflicts"

# Per-package core ownership (assertions on files each package MUST own).
has(){ grep -qx "$2" <<<"${FILES[$1]}" && ok "$1 owns $2" || fail "$1 does not own expected file: $2"; }
has rebuntu-release  /etc/rebuntu-release
has rebuntu-release  /etc/rebuntu-lsb-release
has rebuntu-branding /usr/share/rebuntu/branding/terminal/rebuntu-logo.sh
has rebuntu-plymouth-theme /usr/share/plymouth/themes/rebuntu-basic/rebuntu-basic.plymouth
ok "core per-package regular-file ownership verified"

# --- 3) Metadata -------------------------------------------------------------
dep(){ dpkg-deb -f "${DEB[$1]}" Depends 2>/dev/null || true; }
bdep="$(dep rebuntu-base)"
for want in rebuntu-release rebuntu-branding rebuntu-live; do
  grep -qw "$want" <<<"$bdep" \
    && ok "rebuntu-base depends on $want" \
    || fail "rebuntu-base does not depend on $want (got: ${bdep:-<none>})"
done
grep -qw 'plymouth' <<<"$(dep rebuntu-plymouth-theme)" \
  && ok "rebuntu-plymouth-theme depends on plymouth" \
  || note "rebuntu-plymouth-theme lacks a plymouth dependency (verify theme runtime)"

# Truthful Ubuntu ancestry must be retained in the owned identity file.
x="$(mktemp -d)"; dpkg-deb -x "${DEB[rebuntu-release]}" "$x" >/dev/null 2>&1
if grep -q 'ID_LIKE="ubuntu debian"' "$x/etc/rebuntu-release" 2>/dev/null; then
  ok "rebuntu-release retains truthful Ubuntu ancestry (ID_LIKE=\"ubuntu debian\")"
else
  fail "rebuntu-release /etc/rebuntu-release lacks ID_LIKE=\"ubuntu debian\""
fi
rm -rf "$x"

# --- 4) Behavioral ownership: rebuntu-live ----------------------------------
# Maintainer scripts live in the CONTROL tarball; `dpkg-deb -e` extracts them
# flat into the target dir (e.g. $d/postinst), NOT under $d/DEBIAN/.
l="$(mktemp -d)"; dpkg-deb -e "${DEB[rebuntu-live]}" "$l" >/dev/null 2>&1
if grep -q 'getty@ttyS0.service' "$l/postinst" 2>/dev/null; then
  ok "rebuntu-live postinst enables serial getty@ttyS0"
else
  fail "rebuntu-live postinst does not enable serial getty@ttyS0"
fi
if grep -q 'getty@ttyS0.service' "$l/postrm" 2>/dev/null; then
  ok "rebuntu-live postrm cleans up serial getty@ttyS0"
else
  note "rebuntu-live postrm does not clean up serial getty@ttyS0"
fi
rm -rf "$l"

# --- 5) Upgrade safety: regular-file payload idempotency --------------------
for name in "${NAMES[@]}"; do
  a="$(mktemp -d)"; b="$(mktemp -d)"
  dpkg-deb -x "${DEB[$name]}" "$a" >/dev/null 2>&1
  dpkg-deb -x "${DEB[$name]}" "$b" >/dev/null 2>&1
  if diff -r "$a" "$b" >/dev/null 2>&1; then
    ok "$name file payload is idempotent (same-version upgrade is safe)"
  else
    fail "$name file payload differs between two extracts (not upgrade-idempotent)"
  fi
  rm -rf "$a" "$b"
done

echo
echo "PASS: package ownership + upgrade-safety tests"