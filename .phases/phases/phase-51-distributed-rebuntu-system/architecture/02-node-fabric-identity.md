# Node and Fabric Identity

Distinguish machine identity, installation identity, boot/session identity, node identity, principal identity, network address and human-readable hostname.

`hostname != durable node identity`
`IP address != identity`
`network reachability != membership`
`membership != authorization`

A FabricIdentity and NodeIdentity must be durable, typed, cryptographically bindable and represented in Phase 42 without conflating structural knowledge with authority.
