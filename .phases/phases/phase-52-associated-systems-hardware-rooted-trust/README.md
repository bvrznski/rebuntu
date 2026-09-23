# Rebuntu Phase 52 — Associated Systems & Hardware-Rooted Trust

Phase 52 allows autonomous Rebuntu systems or Phase 51 fabrics to establish bounded cryptographic associations without merging administrative authority.

```text
        autonomous Rebuntu A                autonomous Rebuntu B
               |                                   |
         SystemIdentity A                    SystemIdentity B
               |                                   |
               +------ AssociationCeremony --------+
                              |
                  authenticated key agreement
                              |
                         Association
                              |
                         TrustScope
                              |
                    local policy on A/B
                              |
                    typed authorized actions
```

Hard invariants:
- `authentication != association != authorization`
- `transport != trust`
- `association != unrestricted trust`
- private identity keys are never shared with peers
- DH/key agreement alone does not authenticate identity
- hardware authenticators are optional assurance providers
- FIDO/U2F credentials are not assumed exportable/clonable/arbitrary-DH
- AssociationGrant is bounded capability, not general authority
- Phase 47/45 remain policy/execution authorities
- Phase 51 and Phase 52 remain distinct administrative models
- use reviewed cryptography; do not invent primitives
- C++ remains the deterministic native core

Read `AGENT_HANDOFF.md`, `INDEX.md`, all architecture documents and every numbered prompt.
