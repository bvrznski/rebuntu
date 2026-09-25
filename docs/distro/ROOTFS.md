# Rebuntu Root Filesystem

The first rootfs is bootstrapped from Ubuntu and then transformed at the target
filesystem boundary into Rebuntu.

Host Ubuntu identity is never overwritten.

Canonical ancestry remains:

    Debian -> Ubuntu -> Rebuntu

The resulting rootfs contains Rebuntu identity and foundation packages while
continuing to inherit Ubuntu/Debian userspace and package infrastructure.
