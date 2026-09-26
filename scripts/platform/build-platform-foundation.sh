#!/usr/bin/env bash
set -Eeuo pipefail
R="${REBUNTU_ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/../.."&&pwd)}"
for p in rebuntu-desktop rebuntu-ai rebuntu-ai-dev;do "$R/packages/meta/$p/build.sh";done
"$R/scripts/repository/build-repository.sh"
"$R/scripts/test/test-platform-foundation.sh"
"$R/scripts/test/test-repository.sh"
"$R/installer/tests/test-installer-foundation.sh"
"$R/scripts/platform/hardware-probe.sh"
