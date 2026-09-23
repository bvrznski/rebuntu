# Architectural clarification — native Linux authority

Applies recursively to every Rebuntu phase, including phases 62–106.

Rebuntu is not a Linux reimplementation, shadow OS, wrapper-replica, or second source of truth. Linux and mature native subsystems remain authoritative for the mechanics they own. Rebuntu adds semantics above and across those mechanisms: identity, evidence/provenance, desired state, policy/security integration, capability reasoning, planning, verification, reconciliation, recovery, automation, operator interaction and cross-domain coordination.

Providers/adapters must remain narrow typed boundaries. They translate semantic operations to native mechanisms and return observations/evidence. They must not reproduce kernel, systemd, cgroups, namespaces, procfs/sysfs, udev, D-Bus, Netlink, NetworkManager, nftables, PAM/NSS, polkit/sudo, package-manager, filesystem/mount, process/service or scheduler mechanics.

For existing violations, use aggregational morphing: identify native authority; narrow Rebuntu to its distinct semantic responsibility; migrate callers; verify; only then retire redundant mechanics.
