# Rebuntu platform foundation
Outside `/src`, Rebuntu is organized as: Ubuntu upstream -> Rebuntu Debian packages -> Rebuntu APT repository -> live/installed OS -> hardware probe -> future compatibility resolver -> desired-state plan -> Ansible convergence -> verification/doctor. Docker is a workload runtime, not an ISO/rootfs builder. Accelerator compatibility must be resolved outside Ansible.
