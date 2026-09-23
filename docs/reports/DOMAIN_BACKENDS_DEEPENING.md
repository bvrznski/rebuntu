# Domain Backend Deepening

This iteration replaces the generic-only domain mutation path with typed Linux domain backends.

## Implemented
- Process: signal and priority planning; ps-based inspection.
- Services: systemd start/stop/enable/disable, verification and rollback command synthesis.
- Storage: mount/unmount workflows with findmnt verification; destructive formatting remains intentionally outside this generic path.
- Networking: link state mutation and iproute2 JSON inspection.
- NVIDIA GPU: power-limit planning, verification and rollback; nvidia-smi inspection.
- Packages: apt/dpkg install/remove planning and package-state inspection.
- Identity: account lock/unlock and login-shell mutation with getent/passwd verification.
- Shell: default shell mutation through chsh with identity verification.
- Configuration, secrets, terminal and development domains are explicitly read-only in this generic backend; unsafe mutation must go through dedicated workflows.

## Runtime
`DomainRuntime` performs domain planning, policy authorization, backend execution, postcondition verification, rollback-on-verification-failure, journal persistence, state convergence and telemetry.

No shell string interpolation is used by the domain planners; commands are represented as program + argv.

## Verification
Debug build completed. CTest tests 1-45 passed in the first run before the execution time cap; tests 46-49 were then run separately and all passed. Effective result: 49/49 tests passed.
