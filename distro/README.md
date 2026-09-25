# Rebuntu Distribution Layer

Rebuntu is an Ubuntu-derived Linux distribution.

Canonical ancestry:

    Debian -> Ubuntu -> Rebuntu

Architectural principle:

    Rebuntu inherits aggressively and diverges deliberately.

Rebuntu inherits upstream Debian, Ubuntu, Linux, GNU/Linux userspace,
drivers, desktop protocols and package ecosystems by default.

Components are patched, forked or replaced only where a concrete
Rebuntu-specific architectural requirement justifies divergence.

The existing ../src tree contains the Rebuntu runtime/platform software
and is intentionally independent from this distribution integration layer.

Distribution packaging consumes src; it does not own or restructure src.
