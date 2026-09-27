#!/usr/bin/env bash
set -uo pipefail

ROOT="${REBUNTU_ROOT:-/home/bvrznski/rebuntu}"
ISO="$ROOT/build/artifacts/images/rebuntu-resolute-amd64.iso"
BUILDER="${REBUNTU_BUILDER:-rebuntu-builder}"

PASS=0
FAIL=0
WARN=0
SKIP=0

section() {
    printf '\n\033[1;36m===== %s =====\033[0m\n' "$*"
}

pass() {
    ((PASS++))
    printf '\033[1;32mPASS\033[0m  %s\n' "$*"
}

fail() {
    ((FAIL++))
    printf '\033[1;31mFAIL\033[0m  %s\n' "$*"
}

warn() {
    ((WARN++))
    printf '\033[1;33mWARN\033[0m  %s\n' "$*"
}

skip() {
    ((SKIP++))
    printf '\033[1;35mSKIP\033[0m  %s\n' "$*"
}

exists() {
    local path="$1"
    local label="$2"

    if [[ -e "$path" ]]; then
        pass "$label"
    else
        fail "$label -- missing: $path"
    fi
}

command_available() {
    local cmd="$1"

    if command -v "$cmd" >/dev/null 2>&1; then
        pass "command: $cmd"
    else
        warn "command unavailable: $cmd"
    fi
}

cd "$ROOT" || {
    echo "Cannot enter $ROOT" >&2
    exit 2
}

section "REPOSITORY"

if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    pass "Git repository"
    printf 'HEAD  %s\n' "$(git rev-parse --short HEAD)"
else
    fail "Git repository"
fi

for d in \
    branding \
    ci \
    desktop \
    diagnostics \
    distro \
    hardware \
    images \
    installer \
    kernel \
    packages \
    packaging \
    recovery \
    release \
    repository \
    scripts \
    system \
    systemd \
    tests \
    tools \
    upstream
do
    exists "$ROOT/$d" "$d/"
done

section "BUILD TOOLING"

for cmd in \
    git \
    cmake \
    ctest \
    rsync \
    ssh \
    virsh \
    qemu-system-x86_64 \
    xorriso \
    dpkg-deb \
    apt-cache
do
    command_available "$cmd"
done

section "BUILDER VM"

if command -v virsh >/dev/null 2>&1; then
    if virsh -c qemu:///system dominfo "$BUILDER" >/dev/null 2>&1; then
        pass "libvirt domain: $BUILDER"

        state="$(virsh -c qemu:///system domstate "$BUILDER" 2>/dev/null || true)"
        printf '      state: %s\n' "$state"
    else
        fail "libvirt domain: $BUILDER"
    fi
else
    skip "builder VM check -- virsh unavailable"
fi

if [[ -x "$HOME/.local/bin/rebuntu-vm" ]]; then
    pass "rebuntu-vm wrapper"
else
    warn "rebuntu-vm wrapper missing"
fi

if [[ -x "$HOME/.local/bin/rebuntu-build" ]]; then
    pass "rebuntu-build wrapper"
else
    warn "rebuntu-build wrapper missing"
fi

if [[ -x "$HOME/.local/bin/rebuntu-test" ]]; then
    pass "rebuntu-test wrapper"
else
    warn "rebuntu-test wrapper missing"
fi

section "ISO"

if [[ -f "$ISO" ]]; then
    pass "ISO exists"
    printf '      %s\n' "$(du -h "$ISO" | awk '{print $1}')"
else
    fail "ISO missing: $ISO"
fi

if [[ -f "$ISO" ]] && command -v xorriso >/dev/null 2>&1; then

    ISO_LIST="$(
        xorriso -indev "$ISO" -find / -type f -print 2>/dev/null || true
    )"

    for asset in \
        /casper/vmlinuz \
        /casper/initrd \
        /casper/filesystem.squashfs \
        /boot/grub/grub.cfg
    do
        if grep -Fxq "$asset" <<<"$ISO_LIST"; then
            pass "ISO asset: $asset"
        else
            fail "ISO asset missing: $asset"
        fi
    done

    if grep -Fq '/EFI/BOOT/BOOTX64.EFI' <<<"$ISO_LIST"; then
        pass "UEFI bootloader"
    else
        fail "UEFI bootloader missing"
    fi

else
    skip "ISO structural inspection"
fi

section "GRUB CONFIG"

GRUB_CFG="$ROOT/images/iso/config/grub.cfg"

if [[ -f "$GRUB_CFG" ]]; then
    pass "GRUB configuration exists"

    grep -Eq 'linux[[:space:]]+/casper/vmlinuz' "$GRUB_CFG" \
        && pass "GRUB loads /casper/vmlinuz" \
        || fail "GRUB kernel command"

    grep -Eq 'initrd[[:space:]]+/casper/initrd' "$GRUB_CFG" \
        && pass "GRUB loads /casper/initrd" \
        || fail "GRUB initrd command"

    grep -Eq 'quiet[[:space:]]+splash|splash[[:space:]]+quiet' "$GRUB_CFG" \
        && pass "Plymouth kernel arguments" \
        || warn "quiet splash not detected"

else
    fail "GRUB configuration missing"
fi

section "PLYMOUTH"

PLYMOUTH_PACKAGE="$ROOT/packages/branding/rebuntu-plymouth-theme"

exists "$PLYMOUTH_PACKAGE" "Rebuntu Plymouth package"

if grep -Rqs 'FRAMEBUFFER=y' \
    "$ROOT/scripts" \
    "$ROOT/packages" \
    "$ROOT/system" 2>/dev/null
then
    pass "initramfs framebuffer configuration"
else
    warn "FRAMEBUFFER=y not found in platform sources"
fi

section "DESKTOP"

for d in \
    desktop/platform \
    desktop/shell \
    desktop/ui \
    desktop/design \
    desktop/tests
do
    exists "$ROOT/$d" "$d"
done

if grep -RqsEi '\bgnome\b|\bgdm3?\b|\bmutter\b' \
    "$ROOT/desktop" \
    "$ROOT/packages" \
    "$ROOT/distro" 2>/dev/null
then
    pass "GNOME integration references"
else
    warn "GNOME integration not detected"
fi

if grep -RqsEi '\bplasma\b|\bkwin\b|\bsddm\b|kubuntu-desktop' \
    "$ROOT/desktop" \
    "$ROOT/packages" \
    "$ROOT/distro" 2>/dev/null
then
    warn "KDE/Plasma references detected -- audit required"
else
    pass "No obvious KDE desktop dependency"
fi

section "INSTALLER"

for d in \
    installer/config \
    installer/profiles \
    installer/hooks \
    installer/tests
do
    exists "$ROOT/$d" "$d"
done

if find "$ROOT/installer" -type f -size +0c -print -quit 2>/dev/null \
    | grep -q .
then
    pass "Installer contains implementation/configuration files"
else
    fail "Installer appears empty"
fi

section "PACKAGE REPOSITORY"

exists "$ROOT/repository" "repository/"

if find "$ROOT/repository" -type f -name 'Packages*' -print -quit 2>/dev/null \
    | grep -q .
then
    pass "APT Packages index present"
else
    warn "APT Packages index not found"
fi

if find "$ROOT/repository" -type f \
    \( -name 'Release' -o -name 'InRelease' \) \
    -print -quit 2>/dev/null | grep -q .
then
    pass "APT Release metadata present"
else
    warn "APT Release metadata not found"
fi

section "POST-INSTALL / ANSIBLE"

if find "$ROOT" \
    -path "$ROOT/src" -prune -o \
    -type f \
    \( -name '*.yml' -o -name '*.yaml' \) \
    -print 2>/dev/null \
    | grep -qi ansible
then
    pass "Ansible-related YAML detected"
else
    warn "No obvious Ansible post-install implementation"
fi

section "DOCKER"

if grep -RqsEi 'docker|containerd|compose|buildx' \
    "$ROOT/packages" \
    "$ROOT/distro" \
    "$ROOT/system" \
    "$ROOT/scripts" 2>/dev/null
then
    pass "Container integration references"
else
    warn "Docker/container platform integration not detected"
fi

section "AI / GPU"

if grep -RqsEi 'cuda|nvidia|pytorch|torch|llama\.cpp|vllm' \
    "$ROOT/packages" \
    "$ROOT/distro" \
    "$ROOT/hardware" \
    "$ROOT/config" \
    "$ROOT/scripts" 2>/dev/null
then
    pass "AI/GPU integration references"
else
    warn "AI/GPU platform integration not detected"
fi

section "TEST INFRASTRUCTURE"

for d in \
    tests/distro \
    tests/hardware \
    tests/images \
    tests/integration \
    tests/native \
    tests/unit
do
    exists "$ROOT/$d" "$d"
done

printf '\n'
printf '\033[1m========================================\033[0m\n'
printf '\033[1mREBUNTU PLATFORM AUDIT SUMMARY\033[0m\n'
printf '\033[1m========================================\033[0m\n'
printf '\033[1;32mPASS\033[0m : %d\n' "$PASS"
printf '\033[1;31mFAIL\033[0m : %d\n' "$FAIL"
printf '\033[1;33mWARN\033[0m : %d\n' "$WARN"
printf '\033[1;35mSKIP\033[0m : %d\n' "$SKIP"
printf '\033[1m========================================\033[0m\n'

if (( FAIL > 0 )); then
    exit 1
fi

exit 0
