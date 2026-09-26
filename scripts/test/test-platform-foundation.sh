#!/usr/bin/env bash
set -Eeuo pipefail
R="${REBUNTU_ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/../.."&&pwd)}"; bad=0
for f in scripts/repository/build-repository.sh config/profiles/{base,desktop,ai,ai-dev}.conf packages/meta/{rebuntu-desktop,rebuntu-ai,rebuntu-ai-dev}/DEBIAN/control desktop/session/{rebuntu.desktop,rebuntu.session} installer/autoinstall/user-data.example automation/ansible/playbooks/{base,desktop,docker,ai}.yml scripts/platform/hardware-probe.sh diagnostics/rebuntu-doctor.sh; do [[ -s "$R/$f" ]]&&echo "PASS $f"||{ echo "FAIL $f";bad=1;};done
! grep -RqsEi '\b(plasma-desktop|kwin|sddm|kubuntu-desktop)\b' "$R/packages/meta/rebuntu-desktop" "$R/desktop"||{ echo FAIL_KDE;bad=1;}
grep -q REPLACE_ME "$R/installer/autoinstall/user-data.example"||{ echo FAIL_INSTALLER_SAFETY;bad=1;}
while read -r f;do bash -n "$f"||bad=1;done < <(find "$R/scripts/repository" "$R/scripts/platform" "$R/scripts/postinstall" "$R/diagnostics" -type f -perm -u+x)
((bad==0))
