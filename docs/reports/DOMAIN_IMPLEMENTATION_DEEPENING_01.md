# Domain implementation deepening 01

This pass replaces part of the broad command-only Linux-domain surface with native C++20 state discovery models.

Implemented:
- storage: sysfs block-device inventory, mountinfo parsing, longest-prefix mount resolution;
- networking: sysfs interface counters/state and `/proc/net/route` IPv4 route parsing;
- GPU: PCI/sysfs inventory and display-controller/driver detection independent of NVIDIA CLI;
- processes: robust `/proc/<pid>/stat` parsing (including names containing spaces), cmdline and PID start-time identity;
- services: structured `systemctl show` parser and unit-name validation.

The existing mutation planner/runtime remains intact. These discovery components are deliberately independently testable against injected sysfs/procfs roots, so tests do not mutate the host and future reconciliation can consume typed state instead of scraping command output.
