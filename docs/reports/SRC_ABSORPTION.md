# Canonical src absorption

The former `cpp/include/system` and `cpp/src` implementation trees were classified and absorbed into canonical `src/` responsibilities. Linux-facing mechanics are placed under `providers/linux` or domain-native provider boundaries; semantic/control responsibilities remain outside providers. Phase-number coverage translation units are quarantined under `src/support/phase_coverage_legacy` and are not architectural authorities.

The migration preserves implementation code while allowing subsequent aggregational morphing and caller migration.

## Verification performed in this pass

- `cpp/` implementation tree removed after copying/classifying its implementation into canonical `src/`.
- Native inventory/parsing implementations for storage, networking, accelerators, identity, software, processes and services compile from their canonical domain locations with `-std=c++20 -Wall -Wextra -Wpedantic`.
- Existing service and process reconciliation tests pass from canonical `src/`.
- Added storage reconciliation with a narrow filesystem provider and authoritative re-observation; its test passes with `-Werror`.
- Legacy phase-number translation units are quarantined under `src/support/phase_coverage_legacy`; they are retained only as migration evidence and are not canonical architecture.

## Native authority rule

Domain code owns semantic identity, intent, desired state, planning inputs and verification meaning. Provider code owns only typed translation to/from the authoritative Linux facility. Reconciliation always re-observes native state after actuation instead of treating the requested operation as truth.
