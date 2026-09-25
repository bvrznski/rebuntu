# Rebuntu Desktop Performance Contract

Core principle:

    Don't render, transform, copy or composite a pixel unless necessary.

Corollary:

    A static desktop should be computationally boring.

The graphics architecture should prefer:

- damage-limited rendering
- direct scanout when possible
- zero-copy / dma-buf paths
- output-local rendering
- avoidance of unnecessary cross-GPU transfers
- explicit frame latency and presentation telemetry
