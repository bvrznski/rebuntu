# Rebuntu Distribution Layer

Canonical ancestry:

    Debian -> Ubuntu -> Rebuntu

Architectural principle:

    Rebuntu inherits aggressively and diverges deliberately.

The existing `src/` tree is the Rebuntu runtime/platform implementation.
The distro layer packages and integrates it; it does not copy, mirror,
reorganize, or reimplement it.
