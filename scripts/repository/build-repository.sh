#!/usr/bin/env bash
set -Eeuo pipefail
SUITE="${UBUNTU_SUITE:-resolute}"
R="${REBUNTU_ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/../.."&&pwd)}"; X="$R/repository"; P="$X/pool/main/r/rebuntu"; D="$X/dists/$SUITE"; B="$D/main/binary-amd64"
command -v dpkg-scanpackages >/dev/null || { echo "install dpkg-dev"; exit 2; }
mkdir -p "$P" "$B"; find "$P" -name '*.deb' -delete; rm -f "$B"/Packages* "$D"/{Release,InRelease,Release.gpg}
declare -A S
while IFS= read -r -d '' f; do
 n="$(dpkg-deb -f "$f" Package)"; v="$(dpkg-deb -f "$f" Version)"; a="$(dpkg-deb -f "$f" Architecture)"; k="$n|$v|$a"
 [[ ${S[$k]+x} ]]&&continue; S[$k]=1; install -m644 "$f" "$P/${n}_${v}_${a}.deb"
done < <(find "$R/build/artifacts/deb" "$R/packages" -type f -name '*.deb' -print0 2>/dev/null)
find "$P" -name '*.deb'|grep -q . || { echo "no debs"; exit 3; }
(cd "$X"; dpkg-scanpackages --multiversion pool/main/r/rebuntu /dev/null > dists/$SUITE/main/binary-amd64/Packages)
gzip -n9c "$B/Packages">"$B/Packages.gz"; xz -9ec "$B/Packages">"$B/Packages.xz"
cat >"$D/Release" <<REL
Origin: Rebuntu
Label: Rebuntu
Suite: $SUITE
Codename: $SUITE
Architectures: amd64 all
Components: main
Description: Rebuntu package repository
Date: $(LC_ALL=C date -Ru)
REL
(cd "$D"; echo MD5Sum: >>Release; for f in main/binary-amd64/Packages{,.gz,.xz}; do printf ' %s %16d %s\n' "$(md5sum "$f"|cut -d' ' -f1)" "$(stat -c%s "$f")" "$f">>Release; done; echo SHA256: >>Release; for f in main/binary-amd64/Packages{,.gz,.xz}; do printf ' %s %16d %s\n' "$(sha256sum "$f"|cut -d' ' -f1)" "$(stat -c%s "$f")" "$f">>Release; done)
echo "repository built: $(find "$P" -name '*.deb'|wc -l) packages"
