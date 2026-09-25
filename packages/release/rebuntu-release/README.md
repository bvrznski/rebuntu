# rebuntu-release

Canonical distribution identity package for Rebuntu.

Ancestry:

    Debian -> Ubuntu -> Rebuntu

Principle:

    Rebuntu inherits aggressively and diverges deliberately.

This package deliberately does not overwrite the host's /etc/os-release
during early development.

The development identity is exposed as:

    /etc/rebuntu-release

Replacement/integration with os-release belongs to the image-building
stage, where Rebuntu owns the complete root filesystem.
