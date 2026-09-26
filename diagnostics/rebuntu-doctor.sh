#!/usr/bin/env bash
set -uo pipefail
P=0;F=0;W=0; pass(){((P++));echo "PASS $*";};warn(){((W++));echo "WARN $*";};fail(){((F++));echo "FAIL $*";}
[[ -r /etc/os-release ]]&&pass os-release||fail os-release
grep -qi rebuntu /etc/os-release 2>/dev/null&&pass identity||warn "host is not Rebuntu"
command -v python3>/dev/null&&pass "python3 $(python3 --version 2>&1)"||fail python3
command -v NetworkManager>/dev/null&&pass NetworkManager||warn NetworkManager
command -v gnome-shell>/dev/null&&pass GNOME||warn GNOME
if command -v docker>/dev/null;then docker info>/dev/null 2>&1&&pass Docker||warn "Docker daemon";else warn Docker;fi
if command -v nvidia-smi>/dev/null;then nvidia-smi -L>/dev/null 2>&1&&pass NVIDIA||warn NVIDIA;fi
echo "PASS=$P FAIL=$F WARN=$W";((F==0))
