# Rebuntu Desktop Performance Contract

> Don't render, transform, copy or composite a pixel unless necessary.

> A static desktop should be computationally boring.

Prefer damage-limited rendering, direct scanout, dma-buf/zero-copy,
output-local rendering, minimal cross-GPU transfer, and explicit presentation
telemetry.
