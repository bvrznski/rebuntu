# Cryptographic Protocol

Use modern reviewed cryptographic constructions and libraries; do not invent custom primitives.

Key agreement and peer authentication are separate concerns. Ephemeral authenticated key agreement should provide forward secrecy where feasible.

A Diffie-Hellman-style exchange alone does not authenticate the peer.

Protocol transcripts must bind identities, algorithms, nonces, context, trust scope and relevant channel/session properties to resist MITM, replay and downgrade.
