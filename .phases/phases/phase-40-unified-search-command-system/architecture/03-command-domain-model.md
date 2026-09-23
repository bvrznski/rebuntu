# Command Domain Model

A command is a registered typed capability, not a shell fragment.

`CommandDescriptor` defines canonical identity, target types, arguments, read/mutate class, provider/domain owner, privilege needs, preconditions and documentation. `CommandIntent` binds a descriptor to typed target refs and arguments. Consequential intents produce/hand off to domain-owned plans.

Search context may improve discovery; it never grants authorization.
