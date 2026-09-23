# AGENTS.md

Keep this layer thin. Do not implement systemd, procfs, mount, process signalling, or other native Linux mechanics here. Bind existing semantic controllers to the common reconciliation pipeline and delegate authority to providers/linux. Add tests with fake providers for every new domain binding.
