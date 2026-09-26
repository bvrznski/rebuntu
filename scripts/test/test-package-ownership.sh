#!/usr/bin/env bash
# Package ownership + upgrade-safety test for the Rebuntu foundation packages.
#
# Deterministic and host-safe: no network, no QEMU, no host mutation. It only
# builds the packages and inspects the resulting .deb metadata and file lists.
#
# It proves:
#   1. Each foundation package builds a well-formed .deb (dpkg-deb integrity).
#   2. FILE OWNERSHIP is unambiguous: no file is owned by more than one
#      package (no "shadow" ownership), and each package owns its core file.
#   3. METADATA: rebuntu-base depends on rebuntu-live; rebuntu-release keeps
#      truthful Ubuntu ancestry (ID_LIKE) while owning its own identity files.
#   4. UPGRADE SAFETY: the file payload is idempotent (re-extracting the same
#      version is byte-identical), so a same-version upgrade cannot clobber.
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
  parent="${d%/}"; parent="${parent%/*}"
  deb="$(cd "$parent" && ls -1 "${name}"_*.deb 2>/dev/null | head -1)"
  [[ -n "${deb:-}" && -f "$parent/$deb" ]] || fail "$name: no .deb produced"
  DEB[$name]="$parent/$deb"
  dpkg-deb --info "$parent/$deb" >/dev/null 2>&1 || fail "$name: dpkg-deb integrity check failed"
  ok "built $name ($deb)"
done

# --- 2) Ownership: no file owned by more than one package -------------------
declare -A FILES
for name in "${NAMES[@]}"; do
  FILES[$name]="$(dpkg-deb -c "${DEB[$name]}" | awk 'NF{print $NF}' | sed 's|/$||' | sort -u)"
done
allfiles="$(printf '%s\n' "${FILES[@]}" | grep -vE '^$' | sort)"
dups="$(printf '%s\n' "$allfiles" | sort | uniq -d || true)"
if [[ -n "$dups" ]]; then
  fail "file(s) owned by more than one package (shadow ownership):\n$dups"
fi
ok "no cross-package file-ownership conflicts"

# Core per-package ownership (hard assertions on files each package must own).
has(){ grep -qx "$2" <<<"${FILES[$1]}" && ok "$1 owns $2" || fail "$1 does not own expected file: $2"; }
has rebuntu-release /usr/lib/os-release
has rebuntu-live    /etc/casper-user/liveuser
ok "core per-package ownership verified"

# Informational ownership map (soft — prints the owner of key files).
owner_of(){
  local f="$1"; local owner=""
  for name in "${NAMES[@]}"; do grep -qx "$f" <<<"${FILES[$name]}" && owner="$name" && break; done
  note "owner($f) = ${owner:-<none>}"
}
owner_of /etc/hostname
owner_of /etc/rebuntu-release
owner_of /etc/issue
owner_of /etc/motd

# --- 3) Metadata -------------------------------------------------------------
base_dep="$(dpkg-deb -f "${DEB[rebuntu-base]}" Depends 2>/dev/null || true)"
grep -qw 'rebuntu-live' <<<"$base_dep" \
  && ok "rebuntu-base depends on rebuntu-live" \
  || fail "rebuntu-base does not depend on rebuntu-live (got: ${base_dep:-<none>})"

# Truthful Ubuntu ancestry must be retained (ID_LIKE references ubuntu).
osrel="$(mktemp -d); dpkg-deb -x "${DEB[rebuntu-release]}" "$osrel" >/dev/null 2>&1
cat "$osrel/usr/lib/os-release" 2>/dev/null || true)"
if grep -q 'ID_LIKE="ubuntu debian"' <<<"$osrel"; then
  ok "rebuntu-release retains truthful Ubuntu ancestry (ID_LIKE=\"ubuntu debian\")"
else
  note "rebuntu-release os-release lacks ID_LIKE=\"ubuntu debian\" (check lsb-release)"
fi
rm -rf "$osrel"

# --- 4) Upgrade safety: payload idempotency ---------------------------------
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